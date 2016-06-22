// testFooldFill.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"



#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <iostream>
#include <vector>

#ifdef _DEBUG
#pragma comment(lib,"cxcore200d.lib")
#pragma comment(lib,"cv200d.lib")
#pragma comment(lib,"highgui200d.lib")
#else
#pragma comment(lib,"cxcore200.lib")
#pragma comment(lib,"cv200.lib")
#pragma comment(lib,"highgui200.lib")
#endif

using namespace std;



namespace Hugo
{
	template <typename T>
	class Range
	{
	public:
		Range():isSet(false){}
		Range(const T& minValue, const T& maxValue):isSet(true),itsMinValue(minValue),itsMaxValue(maxValue)
		{
			if (itsMinValue > itsMaxValue)
				std::swap(itsMinValue,itsMaxValue);
		}
		T Max() const {	return itsMaxValue; }
		T Min() const{ return itsMinValue; }
		bool IsInRange(const T& value) const
		{
			if(!isSet) return true; // not set, pass
			if(value >= itsMinValue && value <= itsMaxValue) 
				return true;
			else 
				return false;
		}
	private:
		T itsMinValue;
		T itsMaxValue;
		bool isSet;
	};
}



bool operator<(const CvScalar& lhs, const CvScalar& rhs)
{
	return (lhs.val[0] < lhs.val[0] && lhs.val[1] < lhs.val[1] && lhs.val[2] < lhs.val[2]);
}

bool operator<=(const CvScalar& lhs, const CvScalar& rhs)
{
	return (lhs.val[0] <= lhs.val[0] && lhs.val[1] <= lhs.val[1] && lhs.val[2] <= lhs.val[2]);
}

bool operator>(const CvScalar& lhs, const CvScalar& rhs)
{
	return !(lhs<=rhs);
}
bool operator>=(const CvScalar& lhs, const CvScalar& rhs)
{
	return !(lhs<rhs);
}








void ThreshRange(const IplImage* src, IplImage* dst, double low, double high = 255)
{
	IplImage* temp;
	assert(src->height == dst->height && src->width == dst->width && src->depth == dst->depth);
	assert(src->nChannels == 1 && dst->nChannels == 1);
	temp = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
	cvSet(dst,cvScalarAll(255));
	if(low != 0)
	{
		cvThreshold(src,temp,low,255,CV_THRESH_BINARY);
		cvAnd(dst,temp,dst);
	}
	if (high != 255)
	{
		cvThreshold(src,temp,high,255,CV_THRESH_BINARY_INV);
		cvAnd(dst,temp,dst);
	}
	cvReleaseImage(&temp);
}


void ThreshColorImage(const IplImage* src, IplImage* dst,CvScalar low,CvScalar high = cvScalarAll(255))
{
	IplImage *temp,*pRedImg,*pGreenImg,*pBlueImg;
	assert(src->height == dst->height && src->width == dst->width && src->depth == dst->depth);
	assert(src->nChannels == 3 && dst->nChannels == 1);

	temp = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
	pRedImg = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
	pGreenImg = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
	pBlueImg = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);

	cvSplit(src,pBlueImg,pGreenImg,pRedImg,NULL);


	cvSet(dst,cvScalarAll(255));
	ThreshRange(pRedImg,temp,low.val[2],high.val[2]);
	cvAnd(dst,temp,dst);
	ThreshRange(pGreenImg,temp,low.val[1],high.val[1]);
	cvAnd(dst,temp,dst);
	ThreshRange(pBlueImg,temp,low.val[0],high.val[0]);
	cvAnd(dst,temp,dst);	
	cvReleaseImage(&temp);
	cvReleaseImage(&pRedImg);
	cvReleaseImage(&pGreenImg);
	cvReleaseImage(&pBlueImg);
}

void MynameWindow() 
{
	cvNamedWindow("Example-out");
	cvNamedWindow("origin");
	cvNamedWindow("Red");
	cvNamedWindow("Green");
	cvNamedWindow("Blue");
	cvNamedWindow("Thesh");
}

void showImage( IplImage* thesh, IplImage* subImg, IplImage * pRedImg, IplImage * pGreenImg, IplImage * pBlueImg, IplImage * maskImg ) 
{
	cvShowImage("Thesh",thesh);
	cvShowImage("origin",subImg);
	cvShowImage("Red",pRedImg);
	cvShowImage("Green",pGreenImg);
	cvShowImage("Blue",pBlueImg);
	cvShowImage("Example-out",maskImg);
}

void SplitImage( IplImage * &pRedImg, IplImage* subImg, IplImage * &pGreenImg, IplImage * &pBlueImg ) 
{

	pRedImg = cvCreateImage(cvGetSize(subImg),IPL_DEPTH_8U,1);
	pGreenImg = cvCreateImage(cvGetSize(subImg),IPL_DEPTH_8U,1);
	pBlueImg = cvCreateImage(cvGetSize(subImg),IPL_DEPTH_8U,1);

	cvSplit(subImg,pBlueImg,pGreenImg,pRedImg,NULL);
}


void destroy() 
{
	cvDestroyWindow("Example-out");
	cvDestroyWindow("origin");
	cvDestroyWindow("Red");
	cvDestroyWindow("Green");
	cvDestroyWindow("Blue");
	cvDestroyWindow("Thesh");
	cvDestroyWindow("Example-out");
}

void DrawBox(CvBox2D box,IplImage* img,CvScalar color = CV_RGB(0,0,255)) 
{ 
	CvPoint2D32f point[4]; 
	int i; 
	for ( i=0; i<4; i++) 
	{ 
		point[i].x = 0; 
		point[i].y = 0; 
	}
	cvBoxPoints(box, point); //计算二维盒子顶点 
	CvPoint pt[4]; 
	for ( i=0; i<4; i++) 
	{ 
		pt[i].x = cvRound(point[i].x); 
		pt[i].y = cvRound(point[i].y); 
	} 
	cvLine( img, pt[0], pt[1],color); 
	cvLine( img, pt[1], pt[2],color); 
	cvLine( img, pt[2], pt[3],color); 
	cvLine( img, pt[3], pt[0],color); 
} 


void ThreshRange( IplImage* subImg, IplImage* thesh ) 
{
	ThreshColorImage(subImg,thesh,CV_RGB(0,0,0),CV_RGB(100,100,100));
	//RGBThreshRange(subImg,thesh,CV_RGB(35,110,70),CV_RGB(50,140,85));


	// 查找轮廓
	CvMemStorage* storage_2 = cvCreateMemStorage(0);
	CvSeq* contours_2 = 0;
	cvFindContours(thesh,storage_2,&contours_2,sizeof(CvContour),CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE);

	cvZero(thesh);
	if(contours_2)
	{
		cvDrawContours(thesh,contours_2,cvScalarAll(255),cvScalarAll(255),10);
	}/**/
	for(;contours_2;contours_2 = contours_2->h_next)
	{
		int count = contours_2->total; // This is number point in contour
		CvRect rect;
		CvBox2D box;

		// Number point must be more than or equal to 6 (for cvFitEllipse_32f).
		if( count < 4 )
			continue;

		CvMat* points_f = cvCreateMat( 1, count, CV_32FC2 );
		CvMat points_i = cvMat( 1, count, CV_32SC2, points_f->data.ptr );
		cvCvtSeqToArray( contours_2, points_f->data.ptr, CV_WHOLE_SEQ );
		cvConvert( &points_i, points_f );

		rect = cvBoundingRect(points_f,1);
		box = cvMinAreaRect2(points_f);

		//cvRectangle(subImg,cvPoint(rect.x,rect.y),cvPoint(rect.x + rect.width ,rect.y + rect.height ),CV_RGB(0,0,255));

		double bili;
		bili = box.size.height /box.size.width ;
		if(bili < 1)
			bili = 1/bili;
		if(bili > 1 && bili < 2)
			DrawBox(box,subImg);
		else if( bili > 20)
			DrawBox(box,subImg);

		cvReleaseMat(&points_f);
	}
}





using namespace Hugo;


vector<CvBox2D> CalcObjectPosition(const IplImage* src,IplImage* view,const Range<CvScalar>& rgb_range,const Range<double>& scale_range = Range<double>(), const Range<int>& size_range =Range<int>())
{
	vector <CvBox2D> retBoxs;
	assert(src->nChannels == 3);
	IplImage* pBinaryImage = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);

	ThreshColorImage(src,pBinaryImage,rgb_range.Min(),rgb_range.Max());
	if(view != NULL) cvCopy(pBinaryImage,view);

	CvMemStorage* storage_2 = cvCreateMemStorage(0);
	CvSeq* contours_2 = 0;
	cvFindContours(pBinaryImage,storage_2,&contours_2,sizeof(CvContour),CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE);
	/*if(view != NULL && contours_2)
	{
		cvDrawContours(view,contours_2,cvScalarAll(255),cvScalarAll(255),10);
	}*/
	for(;contours_2;contours_2 = contours_2->h_next)
	{
		CvBox2D box;
		int count = contours_2->total; // This is number point in contour

		// Number point must be more than or equal to 6 (for cvFitEllipse_32f).
		if( count < 4 )
			continue;

		//contours_2 = cvApproxPoly( contours_2, sizeof(CvContour), storage_2, CV_POLY_APPROX_DP, 3,0);

		CvMat* points_f = cvCreateMat( 1, count, CV_32FC2 );
		CvMat points_i = cvMat( 1, count, CV_32SC2, points_f->data.ptr );
		cvCvtSeqToArray( contours_2, points_f->data.ptr, CV_WHOLE_SEQ );
		cvConvert( &points_i, points_f );

		box = cvMinAreaRect2(points_f);


		double scale;
		int length;

		if(box.size.height > box.size.width)
		{
			length = cvRound(box.size.height);
			scale = box.size.height /box.size.width ;
		}
		else
		{
			length = cvRound(box.size.width);
			scale = box.size.width / box.size.height;
		}

		if(scale_range.IsInRange(scale) && size_range.IsInRange(length))
			retBoxs.push_back(box);
		cvReleaseMat(&points_f);
	}
	cvReleaseImage(&pBinaryImage);
	return retBoxs;
}











void MaskRect( IplImage* maskImg, IplImage* subImg ) 
{
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contour = 0;

	contour = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint) , storage);

	cvFindContours(maskImg,storage,&contour,sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE);

	//contours = cvApproxPoly( contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, 1,0);


	cvZero(maskImg);
	if(contour)
	{
		cvDrawContours(maskImg,contour,cvScalarAll(255),cvScalarAll(255),10);
	}

	// This cycle draw all contours and approximate it by ellipses.
	for(;contour;contour = contour->h_next)
	{
		int count = contour->total; // This is number point in contour
		CvRect rect;
		CvBox2D box;

		// Number point must be more than or equal to 6 (for cvFitEllipse_32f).
		if( count < 50 )
			continue;

		CvMat* points_f = cvCreateMat( 1, count, CV_32FC2 );
		CvMat points_i = cvMat( 1, count, CV_32SC2, points_f->data.ptr );
		cvCvtSeqToArray( contour, points_f->data.ptr, CV_WHOLE_SEQ );
		cvConvert( &points_i, points_f );

		rect = cvBoundingRect(points_f,1);

		box = cvMinAreaRect2(points_f);

		box.center.x = box.center.x -1;
		box.center.y = box.center.y -1;
		//cvRectangle(subImg,cvPoint(rect.x-1,rect.y-1),cvPoint(rect.x + rect.width -1,rect.y + rect.height -1),CV_RGB(255,0,0));

		double bili;
		bili = box.size.height /box.size.width ;
		if(bili < 1)
			bili = 1/bili;
		if(bili > 3 && bili < 4)
			DrawBox(box,subImg,CV_RGB(255,0,0));

		cvReleaseMat(&points_f);
	}
}


void RGBEqualizeHist(const IplImage* src,IplImage* dst)
{
	IplImage *pRedImage,*pGreenImage,*pBlueImage;
	pRedImage = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
	pGreenImage = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
	pBlueImage = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
	cvSplit(src,pBlueImage,pGreenImage,pRedImage,NULL);

	cvEqualizeHist(pRedImage,pRedImage);
	cvEqualizeHist(pGreenImage,pGreenImage);
	cvEqualizeHist(pBlueImage,pBlueImage);
	cvMerge(pBlueImage,pGreenImage,pRedImage,NULL,dst);
	cvReleaseImage(&pRedImage);
	cvReleaseImage(&pGreenImage);
	cvReleaseImage(&pBlueImage);
}






#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH
void fooldfill(IplImage* image)
{
	MynameWindow();

	IplImage* subImg = cvCreateImage(cvSize(500,400),IPL_DEPTH_8U,3);
	IplImage* oriImg = cvCreateImage(cvSize(500,400),IPL_DEPTH_8U,3);
	cvSetImageROI(image,cvRect(1850,1250,500,400));
	cvCopy(image,subImg);
	cvCopy(image,oriImg);
	cvSmooth(subImg,subImg,CV_GAUSSIAN,3,3);
	//RGBEqualizeHist(subImg,subImg);
	IplImage *pGrayImg,*pRedImg,*pGreenImg,*pBlueImg;

	SplitImage(pRedImg, subImg, pGreenImg, pBlueImg);


	pGrayImg = cvCreateImage(cvGetSize(subImg),IPL_DEPTH_8U,1);
	cvCvtColor(subImg,pGrayImg,CV_RGB2GRAY);



	IplImage* rectOut = cvCreateImage(cvGetSize(pGrayImg),IPL_DEPTH_8U,3);
	IplImage* maskImg = cvCreateImage(cvSize(502,402),IPL_DEPTH_8U,1);
	IplImage* di_zuo = cvCreateImage(cvGetSize(pGrayImg),IPL_DEPTH_8U,1);
	cvZero(maskImg);
	int flags;
	flags = 8 | (255 << 8)| CV_FLOODFILL_MASK_ONLY;
	//cvFloodFill(subImg,cvPoint(200,160),cvScalar(0,0,255),CV_RGB(5,10,10),CV_RGB(20,30,10),0,flags,maskImg);



	vector<CvBox2D> vet_boxs;
	vector<CvBox2D> vet_boxs2;	
	vector<CvBox2D> vet_boxs3;	
	vet_boxs = CalcObjectPosition(subImg,di_zuo,Range<CvScalar>(cvScalar(30,40,40),CV_RGB(60,60,60)),Range<double>(1.,2.5),Range<int>(30,80));

	vet_boxs2 = CalcObjectPosition(subImg,NULL,Range<CvScalar>(CV_RGB(200,200,200),cvScalarAll(255)),Range<double>(3.,4.3),Range<int>(200,445));
	//vet_boxs2 = CalcObjectPosition(subImg,di_zuo,Range<CvScalar>(CV_RGB(210,210,235),cvScalarAll(255)),Range<double>(3.,4.3),Range<int>(90,160));
	vet_boxs3 = CalcObjectPosition(subImg,NULL,Range<CvScalar>(CV_RGB(200,190,200),cvScalarAll(255)),Range<double>(10.,200.),Range<int>(200,435));

	if(!vet_boxs2.empty())
	{
		const CvBox2D& box_dizuo = vet_boxs2.front();
		bool PedestalPlan = box_dizuo.size.width > box_dizuo.size.height;
		foreach(CvBox2D& box,vet_boxs)
		{
			bool LockPlan = box.size.width > box.size.height;
			if(PedestalPlan != LockPlan)
				box.angle = box_dizuo.angle + 90;
			else
				box.angle = box_dizuo.angle;
		}
	}
	

	foreach(const CvBox2D& box,vet_boxs)
	{
		DrawBox(box,oriImg);
	}
	foreach(const CvBox2D& box,vet_boxs2)
	{
		DrawBox(box,oriImg,CV_RGB(255,0,0));
	}
	foreach(const CvBox2D& box,vet_boxs3)
	{
		DrawBox(box,oriImg,CV_RGB(0,255,255));
	}



	//ThreshRange(subImg, di_zuo);

	//MaskRect(maskImg, subImg);


	showImage(di_zuo, subImg, pRedImg, pGreenImg, pBlueImg,oriImg);


	cvWaitKey(0);
	destroy();

}

typedef cv::Ptr<IplImage> IplImage_Ptr;

template<class T> class Image
{
private:
	IplImage_Ptr imgp;
public:
	Image(IplImage_Ptr img = IplImage_Ptr()) {imgp=img;}
	~Image(){imgp=0;}
	void operator=(IplImage_Ptr img) {imgp=img;}
	inline T* operator[](const int rowIndx) {
		return ((T *)(imgp->imageData + rowIndx*imgp->widthStep));}
};

struct RgbPixel
{
	unsigned char b,g,r;
};

typedef Image<RgbPixel>       RgbImage;








int _tmain(int argc, char* argv[])
{

	IplImage_Ptr img = cvLoadImage("H:\\project\\天宝电子\\排线检测\\testPic\\1.jpg");

	fooldfill(img);
	


	return 0;
}