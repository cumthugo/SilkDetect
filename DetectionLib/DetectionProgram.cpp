#include "DetectionProgram.hpp"

#include "DetectionUnitFactory.hpp"

void DetectionProgram::Detect( IplImage_Ptr sourceImage,DetectionResult& result )
{
	result.IsPass = true;
	result.ErrorString = ResultFactory::GetInstance()->GetPassString();
	result.ResultImage = cvCloneImage(sourceImage);

	//����ÿ������㷨���Ƚ�ȡ��ͼ�������ж��Եļ���㷨������������д��󣬾ͰѴ�����Ϣ������ȥ��
	foreach(shared_ptr<DetectionUnit> da,*this)
	{
		CvRect ROIImageRect = da->SubImageRect.width == 0 ? cvRect(0,0,sourceImage->width,sourceImage->height) : da->SubImageRect;//δ���ã��͸������ó�ȫ��	
		RestrictRect(ROIImageRect,cvRect(0,0,sourceImage->width,sourceImage->height));					//��Ϊ��Ҫ����Rect�������Ҫ����һ��	
		

		IplImage_Ptr subImage = cvCreateImage(cvSize(ROIImageRect.width,ROIImageRect.height),sourceImage->depth,sourceImage->nChannels);
		cvSetImageROI(sourceImage,ROIImageRect);
		cvCopy(sourceImage,subImage);
		cvResetImageROI(sourceImage);
		
		DetectionResult dr;
		da->Detect(subImage,dr);
		
		itsScreenShot.Save(da->Name,subImage,da); //add in 2015/4/28

		//report
		result.Report.push_back(make_shared<ReportUnit>());
		copy(dr.Report.begin(),dr.Report.end(),back_inserter(result.Report));


		if(!dr.IsPass)
		{
			result.IsPass = dr.IsPass;
			result.ErrorString = dr.ErrorString;
			
			cvSetImageROI(result.ResultImage,ROIImageRect);
			cvCopy(dr.ResultImage,result.ResultImage);
			cvResetImageROI(result.ResultImage);
			return;
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