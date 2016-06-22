#include "DetectionProgram.hpp"

#include "DetectionUnitFactory.hpp"


//This function is used for check iterator is valid		--added in 2014/07/22
template <typename T>
bool IsIteartorInList(std::list<T>& l, typename std::list<T>::iterator it)
{
	for (std::list<T>::iterator iter = l.begin(); iter!=l.end(); ++iter)
	{
		if(it == iter) return true;
	}
	return false;
}

//The logic is tested by DetectLogic.	--added in 2014/07/22
//重构 2014/07/22

void DetectionProgram::Detect( IplImage_Ptr sourceImage,DetectionResult& result )
{	
	result.ErrorCode = RESULT_PASS;
	result.ResultImage = cvCloneImage(sourceImage);

	if(!IsIteartorInList(*this,lock_iter))	UnLock(); // if not exist any more, reset detect. --added in 2014/07/22

	if(!IsLock()) //normal detect	--added in 2014/07/22
	{
		//遍历每个检测算法，先截取子图，在运行独自的检测算法，最后如果检测有错误，就把错误信息拷贝过去。		
		for(auto it = this->begin(); it != this->end(); ++it)
		{			
			IplImage_Ptr subImage = GetSubImage(sourceImage,it);
			DetectionResult dr;
			(*it)->Detect(subImage,dr);

			//report
			result.AddUnitReport();
			copy(dr.Report.begin(),dr.Report.end(),back_inserter(result.Report));

			// lock silk error
			if(dr.ErrorCode == RESULT_FAIL_SILK) Lock(it);

			if(!dr.IsPass())
			{				
				result.ErrorCode = dr.ErrorCode;
				CopyResult2Source(result.ResultImage,it,dr.ResultImage);
				break;
			}
		}
	}
	else		//The logic is tested by DetectLogic.	--added in 2014/07/22
	{
		IplImage_Ptr subImage = GetSubImage(sourceImage,lock_iter);
		DetectionResult dr;
		Clock_MS cl;
		cl.Start();
		(*lock_iter)->Detect(subImage,dr);
		cl.Stop();

		result.AddUnitReport();
		if(dr.ErrorCode == RESULT_FAIL_CABLE)		// only cable error could unlock silk error
		{
			//report as normal			
			copy(dr.Report.begin(),dr.Report.end(),back_inserter(result.Report));		
		
			result.ErrorCode = dr.ErrorCode;
			CopyResult2Source(result.ResultImage,lock_iter,dr.ResultImage);			

			//unlock at the end of this function, or CopyResult2Source will be error.
			UnLock();
		}
		else		// set silk error
		{
			//report as silk error			
			result.AddItemReport((*lock_iter)->Name,"丝印",false,cl.GetTime());
			
			result.ErrorCode = RESULT_FAIL_SILK;
			cvAddS(subImage,CV_RGB(100,0,0),subImage);
			CopyResult2Source(result.ResultImage,lock_iter,subImage);		
		}		
	}
}


ptree DetectionProgram::GetTree() const
{
	ptree pt = NamedItem::GetTree();
	foreach(const shared_ptr<DetectionUnit>& du,*this)
	{
		pt.add_child("DetectionUnits.DetectionUnit",du->GetTree());
	}
	return pt;
}

void DetectionProgram::ReadFromTree( const wptree& wpt )
{
	NamedItem::ReadFromTree(wpt);
	if(wpt.find(L"DetectionUnits") != wpt.not_found())
	{
		foreach(const wptree::value_type& v, wpt.get_child(L"DetectionUnits"))
		{
			shared_ptr<DetectionUnit> du = DetectionUnitFactory::CreateUnitFromTree(v.second);
			push_back(du);
		}
	}


}

void DetectionProgram::UpItem( iterator pos )
{
	if(pos != begin())
	{
		iterator current_pos = pos--;
		std::swap(*pos,*current_pos);
	}
}

void DetectionProgram::CopyOf( const DetectionProgram& dp )
{
	Name = dp.Name;
	clear();
	foreach(const shared_ptr<DetectionUnit>& du,dp)
	{
		push_back(du->Clone());
	}
}

IplImage_Ptr DetectionProgram::GetSubImage( IplImage_Ptr sourceImage, iterator& it )
{
	if(!IsIteartorInList(*this,it)) return IplImage_Ptr();
	shared_ptr<DetectionUnit> da = *it;
	CvRect ROIImageRect = GetROIRect(sourceImage,it);

	IplImage_Ptr subImage = cvCreateImage(cvSize(ROIImageRect.width,ROIImageRect.height),sourceImage->depth,sourceImage->nChannels);
	cvSetImageROI(sourceImage,ROIImageRect);
	cvCopy(sourceImage,subImage);
	cvResetImageROI(sourceImage);

	return subImage;
}

CvRect DetectionProgram::GetROIRect( IplImage_Ptr sourceImage, iterator& it )
{
	if(!IsIteartorInList(*this,it)) return cvRect(0,0,0,0);
	shared_ptr<DetectionUnit> da = *it;
	CvRect ROIImageRect = da->SubImageRect.width == 0 ? cvRect(0,0,sourceImage->width,sourceImage->height) : da->SubImageRect;//未设置，就给它设置成全部	
	RestrictRect(ROIImageRect,cvRect(0,0,sourceImage->width,sourceImage->height));					//因为需要修正Rect，因此需要拷贝一份	
	return ROIImageRect;
}

void DetectionProgram::CopyResult2Source( IplImage_Ptr sourceResultImage, iterator it, IplImage_Ptr resultImage )
{
	CvRect ROIImageRect = GetROIRect(sourceResultImage,it);
	cvSetImageROI(sourceResultImage,ROIImageRect);	
	cvCopy(resultImage,sourceResultImage);
	cvResetImageROI(sourceResultImage);
}

bool operator==( const DetectionProgram& lhs, const DetectionProgram& rhs )
{
	return lhs.Name == rhs.Name && lhs.size() == rhs.size();
}

bool operator!=( const DetectionProgram& lhs, const DetectionProgram& rhs )
{	
	return !(lhs == rhs);
}

ostream& operator<<( ostream& o, const DetectionProgram& rhs )
{
	cout << rhs.Name << endl;
	return o;
}