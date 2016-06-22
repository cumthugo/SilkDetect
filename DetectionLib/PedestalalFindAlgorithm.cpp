#include "PedestalFindAlgorithm.hpp"


CvRect PedestalFindAlgorithm::DetectObject( const IplImage_Ptr sourceImage)
{
	IplImage_Ptr dizuoImage = cvCreateImage(cvGetSize(sourceImage),IPL_DEPTH_8U,1);
	ThreshColorImage(sourceImage,dizuoImage,ColorRange);


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
		CutBox(sourceImage, box);
		cvReleaseMat(&points_f);
		double scale = (double)box.width / box.height;
		int size = box.width;
		if(ScaleRange.IsInRange(scale) && SizeRange.IsInRange(size))
			return box;
	}
	return cvRect(0,0,0,0);
}
void PedestalFindAlgorithm::CutBox( const IplImage_Ptr sourceImage, CvRect &box )
{
	while(XColorCount(sourceImage,ColorRange,box.x,box.y,box.width) < XLeastPointNumber)
	{
		box.y ++;
		box.height--;
		if(box.height < 2) break;
	}
	while(XColorCount(sourceImage,ColorRange,box.x,box.y+box.height,box.width) < XLeastPointNumber)
	{
		box.height--;
		if(box.height < 2) break;
	}
	while(YColorCount(sourceImage,ColorRange,box.x,box.y,box.height) < YLeastPointNumber)
	{
		box.x ++;
		box.width --;
		if(box.width < 2) break;
	}
	while(YColorCount(sourceImage,ColorRange,box.x+box.width,box.y,box.height) < YLeastPointNumber)
	{
		box.width --;
		if(box.width < 2) break;
	}
}


ptree PedestalFindAlgorithm::GetTree() const
{
	ptree pt;
	pt.put("type",GetTypeId());
	pt.put_child("ColorRange.Min",GetColorTree(ColorRange.Min()));
	pt.put_child("ColorRange.Max",GetColorTree(ColorRange.Max()));
	pt.put("SizeRange.Min",SizeRange.Min());
	pt.put("SizeRange.Max",SizeRange.Max());
	pt.put("ScaleRange.Min",ScaleRange.Min());
	pt.put("ScaleRange.Max",ScaleRange.Max());

	pt.put("XLeastPointNumber",XLeastPointNumber);
	pt.put("YLeastPointNumber",YLeastPointNumber);
	return pt;
}

void PedestalFindAlgorithm::ReadFromTree( const wptree& wpt )
{
	CvScalar color_from,color_to;
	int size_from,size_to;
	double scale_from,scale_to;

	color_from = ReadColorFromTree(wpt.get_child(L"ColorRange.Min"));
	color_to = ReadColorFromTree(wpt.get_child(L"ColorRange.Max"));
	ColorRange = Range<CvScalar>(color_from,color_to);
	size_from = wpt.get<int>(L"SizeRange.Min");
	size_to = wpt.get<int>(L"SizeRange.Max");
	SizeRange = Range<int>(size_from,size_to);
	scale_from = wpt.get<double>(L"ScaleRange.Min");
	scale_to = wpt.get<double>(L"ScaleRange.Max");
	ScaleRange = Range<double>(scale_from,scale_to);
	XLeastPointNumber = wpt.get<int>(L"XLeastPointNumber");
	YLeastPointNumber = wpt.get<int>(L"YLeastPointNumber");
}

shared_ptr<PedestalFindAlgorithm> PedestalFindAlgorithm::GetFinderFromTree( const wptree& wpt )
{
	shared_ptr<PedestalFindAlgorithm> Finder;
	int class_type = wpt.get<int>(L"type");
	switch (class_type)
	{
	case SimplePedestalFinder::TYPE_ID:
		Finder = shared_ptr<PedestalFindAlgorithm>(new SimplePedestalFinder);
		break;
	case ConstHeightPedestalFinder::TYPE_ID:
		Finder = shared_ptr<PedestalFindAlgorithm>(new ConstHeightPedestalFinder);
		break;
	}
	Finder->ReadFromTree(wpt);
	return Finder;
}


bool PedestalFindAlgorithm::IsEqual( const shared_ptr<PedestalFindAlgorithm>& rhs ) const
{
	return GetTypeId() == rhs->GetTypeId() && ColorRange == rhs->ColorRange && SizeRange == rhs->SizeRange && ScaleRange == rhs->ScaleRange;
}





CvRect SimplePedestalFinder::Find( const IplImage_Ptr sourceImage)
{
	return DetectObject(sourceImage);
}


CvRect InclinedPedestalFinder::Find( const IplImage_Ptr sourceImage )
{
	return DetectObject(sourceImage);
}

CvRect InclinedPedestalFinder::DetectObject( const IplImage_Ptr sourceImage )
{
	IplImage_Ptr dizuoImage = cvCreateImage(cvGetSize(sourceImage),IPL_DEPTH_8U,1);
	ThreshColorImage(sourceImage,dizuoImage,ColorRange);


	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contours = 0;
	cvFindContours(dizuoImage,storage,&contours,sizeof(CvContour),CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE);

	for(;contours;contours = contours->h_next)
	{
		CvBox2D box;
		CvRect rect = cvRect(0,0,0,0);
		int& count = contours->total; 

		if( count < 5 )
			continue;

		CvMat* points_f = cvCreateMat( 1, count, CV_32FC2 );
		CvMat points_i = cvMat( 1, count, CV_32SC2, points_f->data.ptr );
		cvCvtSeqToArray( contours, points_f->data.ptr, CV_WHOLE_SEQ );
		cvConvert( &points_i, points_f );

		box = cvMinAreaRect2(points_f);
		cvReleaseMat(&points_f);
		double scale = (double)box.size.width/ box.size.height;
		int size = (int)box.size.width;
		if(ScaleRange.IsInRange(scale) && SizeRange.IsInRange(size))		
		{	
			float angle = box.angle - 90;
			CvMat* rot_mat = cvCreateMat(2,3,CV_32FC1);
			cv2DRotationMatrix(box.center,-angle,1.0,rot_mat);
			IplImage_Ptr dst = cvCreateImage(cvGetSize(sourceImage),IPL_DEPTH_8U,3);
			cvWarpAffine(sourceImage,dst,rot_mat);
			cvNamedWindow("haha",1);
			cvShowImage("haha",dst);
			cvWaitKey();
			cvReleaseMat(&rot_mat);
			return rect;
		}
	}
	return cvRect(0,0,0,0);
}



CvRect ConstHeightPedestalFinder::Find( const IplImage_Ptr sourceImage)
{
	//return cvRect(1,2,3,ExpectHeight);
	CvRect rect = DetectObject(sourceImage);
	if(DIRECTION_FROM_TOP == ReferenceDirection)
	{
		rect.height = ExpectHeight;
	}
	else
	{
		rect.y = rect.y + rect.height - ExpectHeight;
		rect.height = ExpectHeight;
	}
	return rect;
}


ptree ConstHeightPedestalFinder::GetTree() const
{
	ptree pt = PedestalFindAlgorithm::GetTree();
	pt.put("ExpectHeight",ExpectHeight);
	pt.put("ReferenceDirection",ReferenceDirection);
	return pt;
}


void ConstHeightPedestalFinder::ReadFromTree( const wptree& wpt )
{
	PedestalFindAlgorithm::ReadFromTree(wpt);
	ExpectHeight = wpt.get<int>(L"ExpectHeight");
	ReferenceDirection = wpt.get<int>(L"ReferenceDirection");
}




