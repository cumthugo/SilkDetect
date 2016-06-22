#include "ObjectDetectAlgorithm.hpp"
#include <vector>

#define OBJECT_NOT_FIND -1

int ObjectDetectAlgorithm::ObjectChangePosition( const IplImage_Ptr sourceImage, const CvRect& detectRect, const Range<CvScalar>& colorRange,int objectWidth, int scanDirection /*= SCAN_FROM_BOTTOM*/, int detectFlag /*= DETECT_FLAG_APPEAR*/ )
{
	assert(sourceImage->nChannels == 3);
	RgbImage rgb_src(sourceImage);
	bool IsObjectDetected(false);

	int y_from = scanDirection == SCAN_FROM_BOTTOM ? detectRect.y + detectRect.height : detectRect.y;
	int y_to = scanDirection == SCAN_FROM_BOTTOM ? detectRect.y : detectRect.y + detectRect.height;
	int y_index;

	foreach_int(y_index,y_from,y_to)
	{
		int fitCount = XColorCount(sourceImage,colorRange,detectRect.x,y_index,detectRect.width);

		if(detectFlag == DETECT_FLAG_APPEAR)
		{	
			if(fitCount >= objectWidth)
				return y_index;
		}	
		else
		{
			if(fitCount >= objectWidth)
				IsObjectDetected = true; 
			else if (IsObjectDetected && fitCount < objectWidth/2)
				return y_index;
		}
	}
	return OBJECT_NOT_FIND;
}

bool ObjectDetectAlgorithm::isObjectInRect( const IplImage_Ptr sourceImage, const CvRect& detectRect, const Range<CvScalar>& colorRange,int objectWidth, int scanDirection /*= SCAN_FROM_BOTTOM*/, int detectFlag /*= DETECT_FLAG_APPEAR*/ )
{
	return ObjectChangePosition(sourceImage,detectRect,colorRange,objectWidth,scanDirection,detectFlag) != OBJECT_NOT_FIND;
}


void CommonSilkDetectAlgorithm::Detect( const IplImage_Ptr sourceImage,const CvRect& PedestalRect,int PedestalPosition,DetectionResult& result )
{
	result.IsPass = false;
	const int &x(PedestalRect.x),&width(PedestalRect.width);
	//图像的180°旋转只影响到y的值
	int y = PEDESTAL_ON_BOTTOM == PedestalPosition ? PedestalRect.y : (PedestalRect.y + PedestalRect.height);
	int Silk_y = PEDESTAL_ON_BOTTOM == PedestalPosition ? y-SearchRange.Max() : (y + SearchRange.Min());
	int Silk_width = SearchWidth == 0 ? width-2*XOffset : SearchWidth;
	int Silk_height = SearchRange.Max()-SearchRange.Min();
	int LeftSilk_x = x+XOffset;
	int RightSilk_x = x + width - XOffset - Silk_width;
	CvRect LeftSilkRect = cvRect(LeftSilk_x,Silk_y,Silk_width,Silk_height);
	CvRect RightSilkRect = cvRect(RightSilk_x,Silk_y,Silk_width,Silk_height);
	//图像的180°旋转还影响检测的扫描顺序
	ScanDirection SilkScanDir = PEDESTAL_ON_BOTTOM == PedestalPosition ? SCAN_FROM_BOTTOM : SCAN_FROM_TOP;
	//restrict;for safe
	RestrictRect(LeftSilkRect,cvRect(0,0,sourceImage->width,sourceImage->height));
	RestrictRect(RightSilkRect,cvRect(0,0,sourceImage->width,sourceImage->height));

	int Object_Left_y = ObjectChangePosition(sourceImage,LeftSilkRect,ColorRange,PixelCount,SilkScanDir,DetectFlag);
	int Object_Right_y = ObjectChangePosition(sourceImage,RightSilkRect,ColorRange,PixelCount,SilkScanDir,DetectFlag);

	if(Object_Left_y == OBJECT_NOT_FIND || Object_Right_y == OBJECT_NOT_FIND)
	{
		result.ErrorString = ResultFactory::GetInstance()->GetSilkErrorString();
		FillRect(result.ResultImage,LeftSilkRect,CV_RGB(100,0,0));
		FillRect(result.ResultImage,RightSilkRect,CV_RGB(100,0,0));
		return;
	}
	//检测左右的差距
	if(MaxGapAround >= 0)
	{
		if(abs(Object_Left_y-Object_Right_y) > MaxGapAround)
		{
			result.ErrorString = ResultFactory::GetInstance()->GetSilkErrorString();
			FillRect(result.ResultImage,LeftSilkRect,CV_RGB(100,0,0));
			FillRect(result.ResultImage,RightSilkRect,CV_RGB(100,0,0));
			return;
		}
	}
	result.IsPass = true;
}

ptree CommonSilkDetectAlgorithm::GetTree() const
{
	ptree pt;
	pt.put_child("ColorRange.Min",GetColorTree(ColorRange.Min()));
	pt.put_child("ColorRange.Max",GetColorTree(ColorRange.Max()));
	pt.put("SearchRange.Min",SearchRange.Min());
	pt.put("SearchRange.Max",SearchRange.Max());
	pt.put("PixelCount",PixelCount);

	pt.put("XOffset",XOffset);
	pt.put("SearchWidth",SearchWidth);
	pt.put("MaxGapAround",MaxGapAround);

	return pt;
}

void CommonSilkDetectAlgorithm::ReadFromTree( const wptree& wpt )
{
	CvScalar color_from,color_to;
	int size_from,size_to;
	color_from = ReadColorFromTree(wpt.get_child(L"ColorRange.Min"));
	color_to = ReadColorFromTree(wpt.get_child(L"ColorRange.Max"));
	ColorRange = Range<CvScalar>(color_from,color_to);
	size_from = wpt.get<int>(L"SearchRange.Min");
	size_to = wpt.get<int>(L"SearchRange.Max");
	SearchRange = Range<int>(size_from,size_to);
	PixelCount = wpt.get<int>(L"PixelCount");

	XOffset = wpt.get<int>(L"XOffset",0);
	SearchWidth = wpt.get<int>(L"SearchWidth",0);
	MaxGapAround = wpt.get<int>(L"MaxGapAround",-1);

}
bool operator==( const CommonSilkDetectAlgorithm& lhs, const CommonSilkDetectAlgorithm& rhs )
{
	return  lhs.ColorRange == rhs.ColorRange &&
			lhs.SearchRange == rhs.SearchRange &&
			lhs.PixelCount == rhs.PixelCount;
}

bool operator!=( const CommonSilkDetectAlgorithm& lhs, const CommonSilkDetectAlgorithm& rhs )
{
	return !(lhs == rhs);
}

ostream& operator<<( ostream& o, const CommonSilkDetectAlgorithm& rhs )
{
	o << rhs.ColorRange << rhs.SearchRange << rhs.PixelCount;
	return o;
}


void FrontLockDetectAlgorithm::Detect( const IplImage_Ptr sourceImage,const CvRect& PedestalRect,int PedestalPosition,DetectionResult& result )
{
	result.IsPass = false;
	const int &x(PedestalRect.x),&width(PedestalRect.width);
	//图像的180°旋转只影响到y的值
	int y = PEDESTAL_ON_BOTTOM == PedestalPosition ? PedestalRect.y : (PedestalRect.y + PedestalRect.height);
	int Lock_y = PEDESTAL_ON_BOTTOM == PedestalPosition ? y -SearchRange.Max() : (y + SearchRange.Min());
	ScanDirection LockScanDir = PEDESTAL_ON_BOTTOM == PedestalPosition ? SCAN_FROM_BOTTOM : SCAN_FROM_TOP;

	CvRect LeftLockRect = cvRect(x-XOffset,Lock_y,SearchWidth,SearchRange.Max()-SearchRange.Min());
	CvRect RightLockRect = cvRect(x+width+XOffset-SearchWidth,Lock_y,SearchWidth,SearchRange.Max()-SearchRange.Min());

	RestrictRect(LeftLockRect,cvRect(0,0,sourceImage->width,sourceImage->height));
	RestrictRect(RightLockRect,cvRect(0,0,sourceImage->width,sourceImage->height));

	if(!isObjectInRect(sourceImage,LeftLockRect,ColorRange,PixelCount,LockScanDir,DetectFlag))
	{
		result.ErrorString = ResultFactory::GetInstance()->GetLockErrorString();
		FillRect(result.ResultImage,LeftLockRect,CV_RGB(100,0,0));
		return;
	}
	if(!isObjectInRect(sourceImage,RightLockRect,ColorRange,PixelCount,LockScanDir,DetectFlag))
	{
		result.ErrorString = ResultFactory::GetInstance()->GetLockErrorString();
		FillRect(result.ResultImage,RightLockRect,CV_RGB(100,0,0));
		return;
	}
	result.IsPass = true;
}

ptree FrontLockDetectAlgorithm::GetTree() const
{
	ptree pt;
	pt.put_child("ColorRange.Min",GetColorTree(ColorRange.Min()));
	pt.put_child("ColorRange.Max",GetColorTree(ColorRange.Max()));
	pt.put("SearchRange.Min",SearchRange.Min());
	pt.put("SearchRange.Max",SearchRange.Max());
	pt.put("PixelCount",PixelCount);
	pt.put("XOffset",XOffset);
	pt.put("SearchWidth",SearchWidth);
	return pt;
}

void FrontLockDetectAlgorithm::ReadFromTree( const wptree& wpt )
{
	CvScalar color_from,color_to;
	int size_from,size_to;
	color_from = ReadColorFromTree(wpt.get_child(L"ColorRange.Min"));
	color_to = ReadColorFromTree(wpt.get_child(L"ColorRange.Max"));
	ColorRange = Range<CvScalar>(color_from,color_to);
	size_from = wpt.get<int>(L"SearchRange.Min");
	size_to = wpt.get<int>(L"SearchRange.Max");
	SearchRange = Range<int>(size_from,size_to);
	PixelCount = wpt.get<int>(L"PixelCount");
	XOffset = wpt.get<int>(L"XOffset");
	SearchWidth = wpt.get<int>(L"SearchWidth");
}


bool operator==( const FrontLockDetectAlgorithm& lhs, const FrontLockDetectAlgorithm& rhs )
{
	return  lhs.ColorRange == rhs.ColorRange &&
			lhs.SearchRange == rhs.SearchRange &&
			lhs.PixelCount == rhs.PixelCount &&
			lhs.XOffset == rhs.XOffset &&
			lhs.SearchWidth == rhs.SearchWidth;
}

bool operator!=( const FrontLockDetectAlgorithm& lhs, const FrontLockDetectAlgorithm& rhs )
{
	return !(lhs == rhs);
}

ostream& operator<<( ostream& o, const FrontLockDetectAlgorithm& rhs )
{
	o << rhs.ColorRange << rhs.SearchRange << rhs.PixelCount << rhs.XOffset << rhs.SearchWidth;
	return o;
}


void BackLockDetectAlgorithm::Detect( const IplImage_Ptr sourceImage,const CvRect& PedestalRect,int PedestalPosition,DetectionResult& result )
{
	result.IsPass = false;
	const int &x(PedestalRect.x),&width(PedestalRect.width);
	//图像的180°旋转只影响到y的值
	int y = PedestalPosition == PEDESTAL_ON_BOTTOM ? PedestalRect.y : (PedestalRect.y + PedestalRect.height);
	int Lock_y = PedestalPosition == PEDESTAL_ON_BOTTOM ? y - SearchRange.Max() : y + SearchRange.Min();
	//图像的180°旋转还影响检测的扫描顺序
	ScanDirection ScanDir = PedestalPosition == PEDESTAL_ON_BOTTOM ? SCAN_FROM_BOTTOM : SCAN_FROM_TOP;
	CvRect Rect = cvRect(x,Lock_y,width,SearchRange.Max()-SearchRange.Min());
	//restrict;for safe
	RestrictRect(Rect,cvRect(0,0,sourceImage->width,sourceImage->height));

	if(!isObjectInRect(sourceImage,Rect,ColorRange,PixelCount,ScanDir,DetectFlag))
	{
		result.ErrorString = ResultFactory::GetInstance()->GetLockErrorString();
		FillRect(result.ResultImage,Rect,CV_RGB(100,0,0));
		return;
	}
	result.IsPass = true;
}

ptree BackLockDetectAlgorithm::GetTree() const
{
	ptree pt;
	pt.put_child("ColorRange.Min",GetColorTree(ColorRange.Min()));
	pt.put_child("ColorRange.Max",GetColorTree(ColorRange.Max()));
	pt.put("SearchRange.Min",SearchRange.Min());
	pt.put("SearchRange.Max",SearchRange.Max());
	pt.put("PixelCount",PixelCount);
	return pt;
}

void BackLockDetectAlgorithm::ReadFromTree( const wptree& wpt )
{
	CvScalar color_from,color_to;
	int size_from,size_to;
	color_from = ReadColorFromTree(wpt.get_child(L"ColorRange.Min"));
	color_to = ReadColorFromTree(wpt.get_child(L"ColorRange.Max"));
	ColorRange = Range<CvScalar>(color_from,color_to);
	size_from = wpt.get<int>(L"SearchRange.Min");
	size_to = wpt.get<int>(L"SearchRange.Max");
	SearchRange = Range<int>(size_from,size_to);
	PixelCount = wpt.get<int>(L"PixelCount");
}

bool operator==( const BackLockDetectAlgorithm& lhs, const BackLockDetectAlgorithm& rhs )
{
	return  lhs.ColorRange == rhs.ColorRange &&
		lhs.SearchRange == rhs.SearchRange &&
		lhs.PixelCount == rhs.PixelCount;
}

bool operator!=( const BackLockDetectAlgorithm& lhs, const BackLockDetectAlgorithm& rhs )
{
	return !(lhs == rhs);
}

ostream& operator<<( ostream& o, const BackLockDetectAlgorithm& rhs )
{
	o << rhs.ColorRange << rhs.SearchRange << rhs.PixelCount ;
	return o;
}
