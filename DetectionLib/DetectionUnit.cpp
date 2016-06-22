#include "DetectionUnit.hpp"






void DetectionUnit::Detect(IplImage_Ptr sourceImage,DetectionResult& result)
{
	result.ResultImage = cvCloneImage(sourceImage);
	result.ErrorString = ResultFactory::GetInstance()->GetPassString();
	result.IsPass = false;	
	assert(PedestalFinder);
	CvRect FindPedestalRect = PedestalFinder->Find(sourceImage);


	if(FindPedestalRect.width == 0)
	{	
		result.ErrorString = ResultFactory::GetInstance()->GetPedestalErrorString();
		cvAddS(result.ResultImage,CV_RGB(100,0,0),result.ResultImage);
		return;
	}
	FillRect(result.ResultImage,FindPedestalRect,CV_RGB(100,100,0));
	DetectAlgorithm(sourceImage,FindPedestalRect,result);
}

ptree DetectionUnit::GetTree() const
{
	ptree pt =  NamedItem::GetTree();
	pt.put("Type",GetTypeId());
	pt.put("Param.SubRect.x",SubImageRect.x);
	pt.put("Param.SubRect.y",SubImageRect.y);
	pt.put("Param.SubRect.width",SubImageRect.width);
	pt.put("Param.SubRect.height",SubImageRect.height);

	pt.put("Param.PedestalPosition",PedestalPosition);

	pt.put_child("Param.Pedestal",PedestalFinder->GetTree());

	return pt;
}

void DetectionUnit::ReadFromTree( const wptree& wpt )
{
	NamedItem::ReadFromTree(wpt);
	SubImageRect.x = wpt.get<int>(L"Param.SubRect.x");
	SubImageRect.y = wpt.get<int>(L"Param.SubRect.y");
	SubImageRect.width = wpt.get<int>(L"Param.SubRect.width");
	SubImageRect.height = wpt.get<int>(L"Param.SubRect.height");

	PedestalPosition = wpt.get<int>(L"Param.PedestalPosition",PEDESTAL_ON_BOTTOM);

	PedestalFinder = PedestalFindAlgorithm::GetFinderFromTree(wpt.get_child(L"Param.Pedestal"));
}







CvRect DetectionUnit::DetectObject(const IplImage_Ptr sourceImage,const Range<CvScalar>& colorRange, const Range<double>& scaleRange, const Range<int>& lengthRange)
{
	IplImage_Ptr dizuoImage = cvCreateImage(cvGetSize(sourceImage),IPL_DEPTH_8U,1);
	ThreshColorImage(sourceImage,dizuoImage,colorRange);


	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contours = 0;
	cvFindContours(dizuoImage,storage,&contours,sizeof(CvContour),CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE);

	for(;contours;contours = contours->h_next)
	{
		CvRect box;
		int& count = contours->total; 

		if( count < 5 )
			continue;

		CvMat* points_f = cvCreateMat( 1, count, CV_32FC2 );
		CvMat points_i = cvMat( 1, count, CV_32SC2, points_f->data.ptr );
		cvCvtSeqToArray( contours, points_f->data.ptr, CV_WHOLE_SEQ );
		cvConvert( &points_i, points_f );

		box = cvBoundingRect(points_f);
		//这里需要裁剪
		//int ok_width = box.width/2.5;
		int ok_width = 5;
		while(XColorCount(sourceImage,colorRange,box.x,box.y,box.width) < ok_width)
		{
			box.y ++;
			box.height--;
			if(box.height < 2) break;
		}
		while(XColorCount(sourceImage,colorRange,box.x,box.y+box.height,box.width) < ok_width)
		{
			box.height--;
			if(box.height < 2) break;
		}

		cvReleaseMat(&points_f);
		double scale = (double)box.width / box.height;
		int size = box.width;
		if(scaleRange.IsInRange(scale) && lengthRange.IsInRange(size))
			return box;
	}
	return cvRect(0,0,0,0);
}


bool DetectionUnit::IsBasicEqual( const DetectionUnit& rhs ) const
{
	return Name == rhs.Name && SubImageRect == rhs.SubImageRect && 
		PedestalPosition == rhs.PedestalPosition && PedestalFinder->IsEqual(rhs.PedestalFinder);
}
