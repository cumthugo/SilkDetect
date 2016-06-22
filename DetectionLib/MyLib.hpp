#pragma once


#include <string>
#include <list>
using namespace std;

//#include <boost/shared_ptr.hpp>
//using boost::shared_ptr;
#include <boost/format.hpp>
#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

/************************************************************************/
/* OpenCV                                                               */
/************************************************************************/


#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "Range.hpp"

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

struct HsvPixel
{
	unsigned char h,s,v;
};

struct RgbPixelFloat
{
	float b,g,r;
} ;

typedef Image<RgbPixel>       RgbImage;
typedef Image<HsvPixel>		  HsvImage;
typedef Image<RgbPixelFloat>  RgbImageFloat;
typedef Image<unsigned char>  BwImage;
typedef Image<float>          BwImageFloat;


bool operator==(const CvRect& lhs, const CvRect& rhs);
bool operator!=(const CvRect& lhs, const CvRect& rhs);
ostream& operator<<(ostream& o,const CvRect& rhs);

bool operator<(const CvScalar& lhs, const CvScalar& rhs);
bool operator<=(const CvScalar& lhs, const CvScalar& rhs);
bool operator>(const CvScalar& lhs, const CvScalar& rhs);
bool operator>=(const CvScalar& lhs, const CvScalar& rhs);
bool operator==(const CvScalar& lhs, const CvScalar& rhs);
bool operator!=(const CvScalar& lhs, const CvScalar& rhs);
ostream& operator<<(ostream& o,const CvScalar& rhs);

/************************************************************************/
/* 序列化                                                                     */
/************************************************************************/

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
using boost::property_tree::ptree;
using boost::property_tree::wptree;

class TreeSerialization
{
public:
	virtual ~TreeSerialization(){}
	virtual ptree GetTree() const = 0;
	virtual void ReadFromTree(const wptree& wpt) = 0;
};
class NamedItem : public TreeSerialization
{
public:
	
	NamedItem():Name(""){}
	NamedItem(const string& name):Name(name){}
	ptree GetTree() const
	{
		ptree pt;
		pt.put("Name",Name);
		return pt;
	}
	void ReadFromTree(const wptree& wpt)
	{
		wstring wTemp;
		wTemp  = wpt.get<wstring>(L"Name");
		Name = string(wTemp.begin(),wTemp.end());
	}
	string Name;
};

//color serialization
ptree GetColorTree(const CvScalar& color);
CvScalar ReadColorFromTree(const wptree& wpt);



template <typename T>
class NamedItem_Find_PD : public binary_function<T,string,bool>
{
public:
	bool operator()(const T& tpe,const string& UnitName) const
	{
		return tpe.Name == UnitName;
	}
};

template <typename T>
class NamedItem_Ptr_Find_PD : public binary_function<T,string,bool>
{
public:
	bool operator()(const T& tpe,const string& UnitName) const
	{
		return tpe->Name == UnitName;
	}
};

//我的算法
void ThreshColorImage(const IplImage_Ptr src,IplImage_Ptr dst,const Range<CvScalar>& colorRange);
void Rotating180(const IplImage_Ptr src,IplImage_Ptr dst);
IplImage_Ptr Rotate90Clockwise(const IplImage_Ptr& src);
IplImage_Ptr Rotate90CounterClockwise(const IplImage_Ptr& src);
void FillRect(IplImage_Ptr image, const CvRect& rect, const CvScalar& color);
void RestrictRect(CvRect& targetRect,const CvRect& refRect);
int XColorCount(const IplImage_Ptr sourceImage, const Range<CvScalar>& colorRange, int x, int y, int width);
int YColorCount( const IplImage_Ptr sourceImage, const Range<CvScalar>& colorRange, int x, int y, int height );


#define foreach_int(VAR,FROM,TO)	\
	for(VAR = FROM; FROM < TO ? VAR <= TO : VAR >= TO; FROM < TO ? ++VAR : --VAR) 

#define CV_HSV( h, s, v)  cvScalar((h)/2, (s)*2.55, (v)*2.55, 1.)

inline bool IsHSV( const CvScalar& color )
{
	return color.val[3] == 1.;
}
CvScalar CvtRGB2HSV(const CvScalar& rgb_color);


#define PEDESTAL_ON_TOP 0
#define PEDESTAL_ON_BOTTOM 1