#include "MyLib.hpp"




bool operator<(const CvScalar& lhs, const CvScalar& rhs)
{
	return ((lhs.val[0]<rhs.val[0]) && (lhs.val[1] < rhs.val[1]) && (lhs.val[2] < rhs.val[2]));
}

bool operator<=(const CvScalar& lhs, const CvScalar& rhs)
{
	return ((lhs.val[0] <= rhs.val[0]) && (lhs.val[1] <= rhs.val[1]) && (lhs.val[2] <= rhs.val[2]));
}

bool operator>(const CvScalar& lhs, const CvScalar& rhs)
{
	return ((lhs.val[0] > rhs.val[0]) && (lhs.val[1] > rhs.val[1]) && (lhs.val[2] > rhs.val[2]));
}

bool operator>=(const CvScalar& lhs, const CvScalar& rhs)
{
	return ((lhs.val[0] >= rhs.val[0]) && (lhs.val[1] >= rhs.val[1]) && (lhs.val[2] >= rhs.val[2]));
}

bool operator==( const CvScalar& lhs, const CvScalar& rhs )
{
	return ((lhs.val[0] == rhs.val[0]) && (lhs.val[1] == rhs.val[1]) && (lhs.val[2] == rhs.val[2]));
}


bool operator!=( const CvScalar& lhs, const CvScalar& rhs )
{
	return !(lhs==rhs);
}


ostream& operator<<( ostream& o,const CvScalar& rhs )
{
	if(rhs.val[3] == 1)
		o << "H-" << rhs.val[0] << "  S-" << rhs.val[1] << "  V-" << rhs.val[2];
	else
		o << "R-" << rhs.val[2] << "  G-" << rhs.val[1] << "  B-" << rhs.val[0];
	return o;
}

bool operator==( const CvRect& lhs, const CvRect& rhs )
{
	return lhs.x == rhs.x &&
		lhs.y == rhs.y &&
		lhs.width == rhs.width &&
		lhs.height == rhs.height;
}
bool operator!=( const CvRect& lhs, const CvRect& rhs )
{
	return !(lhs==rhs);
}

ostream& operator<<( ostream& o,const CvRect& rhs )
{
	o << "Rect: x=" << rhs.x << " y=" << rhs.y << " width=" << rhs.width << " height=" << rhs.height;
	return o;
}





void ThreshColorImage(const IplImage_Ptr src,IplImage_Ptr dst,const Range<CvScalar>& colorRange)
{
	assert(src->height == dst->height && src->width == dst->width && src->depth == dst->depth);
	assert(src->nChannels == 3 && dst->nChannels == 1);

	IplImage_Ptr src_copy = cvCloneImage(src);
	if(IsHSV(colorRange.Min()))
	{	
		cvCvtColor(src,src_copy,CV_BGR2HSV);
	}
	RgbImage rgb_src(src_copy);
	BwImage single_dst(dst);

	for (int i=0;i<src_copy->height;i++)
	{
		for (int j=0;j<src_copy->width;j++)
		{
			if(colorRange.IsInRange(CV_RGB(rgb_src[i][j].r,rgb_src[i][j].g,rgb_src[i][j].b))) 
				single_dst[i][j] = 255;
			else 
				single_dst[i][j] = 0;
		}
	}
}

void Rotating180(const IplImage_Ptr src,IplImage_Ptr dst)
{
	assert(src->height == dst->height && src->width == dst->width && src->depth == dst->depth);
	assert(src->nChannels == 3 && dst->nChannels == 3);
	IplImage_Ptr src_copy = cvCloneImage(src);
	RgbImage srcImg(src_copy),dstImg(dst);
	for(int row_index = 0;row_index < src->height; row_index++)
	{
		for(int col_index = 0; col_index < src->width; col_index++)
		{
			dstImg[src->height - row_index - 1][src->width - col_index - 1] = srcImg[row_index][col_index];
		}
	}
}

void FillRect( IplImage_Ptr image, const CvRect& rect, const CvScalar& color )
{
	assert(image->nChannels == 3);
	CvRect restrictRect(rect);
	RestrictRect(restrictRect,cvRect(0,0,image->width,image->height));
	cvSetImageROI(image,rect);
	cvAddS(image,color,image);
	cvResetImageROI(image);
}

void RestrictRect( CvRect& targetRect,const CvRect& refRect )
{
	int x_min = refRect.x;
	int x_max = refRect.x + refRect.width;
	int y_min = refRect.y;
	int y_max = refRect.y + refRect.height;

	if(targetRect.width > refRect.width)
		targetRect.width = refRect.width;
	if(targetRect.height > refRect.height)
		targetRect.height = refRect.height;

	if(targetRect.x < x_min)
		targetRect.x = x_min;
	if(targetRect.x + targetRect.width > x_max)
		targetRect.x = x_max - targetRect.width;

	if(targetRect.y < y_min)
		targetRect.y = y_min;
	if(targetRect.y + targetRect.height > y_max)
		targetRect.y = y_max - targetRect.height;
}




CvScalar CvtRGB2HSV( const CvScalar& rgb_color )
{
	double r(rgb_color.val[2]),g(rgb_color.val[1]),b(rgb_color.val[0]); 
	double h,s,v;
	double rgb_max = max(max(r,g),b);
	double rgb_min = min(min(r,g),b);
	v = rgb_max;
	s = v == 0 ? 0 : (v - rgb_min)/v;
	if(v == r)
		h = 60*(g - b)/(v - rgb_min);
	else if (v == g)
		h = 120 + 60*(b - r)/(v - rgb_min);
	else
		h = 240 + 60*(r - g)/(v - rgb_min);
	if(h < 0)
		h += 360;

	return CV_HSV(h,s*100,v/2.55);
}

int XColorCount( const IplImage_Ptr sourceImage, const Range<CvScalar>& colorRange, int x, int y, int width )
{
	assert(sourceImage->nChannels == 3);
	RgbImage rgb_src(sourceImage);
	int fitCount = 0;
	int x_index;
	foreach_int(x_index,x,x+width)
	{
		RgbPixel& pix = rgb_src[y][x_index];
		CvScalar pixelColor = CV_RGB(pix.r,pix.g,pix.b);
		if(IsHSV(colorRange.Min()))
		{
			pixelColor = CvtRGB2HSV(pixelColor);
		}
		if(colorRange.IsInRange(pixelColor))
			fitCount++;
	}
	return fitCount;
}

int YColorCount( const IplImage_Ptr sourceImage, const Range<CvScalar>& colorRange, int x, int y, int height )
{
	assert(sourceImage->nChannels == 3);
	RgbImage rgb_src(sourceImage);
	int fitCount = 0;
	int y_index;
	foreach_int(y_index,y,y+height)
	{
		RgbPixel& pix = rgb_src[y_index][x];
		CvScalar pixelColor = CV_RGB(pix.r,pix.g,pix.b);
		if(IsHSV(colorRange.Min()))
		{
			pixelColor = CvtRGB2HSV(pixelColor);
		}
		if(colorRange.IsInRange(pixelColor))
			fitCount++;
	}
	return fitCount;
}




#define COLOR_RGB_TYPE 0
#define COLOR_HSV_TYPE 1

ptree GetColorTree( const CvScalar& color )
{
	ptree pt;
	if(IsHSV(color))
	{
		pt.put("type",COLOR_HSV_TYPE);
		pt.put("H",color.val[0]*2);
		pt.put("S",cvRound(color.val[1]/2.55));
		pt.put("V",cvRound(color.val[2]/2.55));
	}
	else
	{
		pt.put("type",COLOR_RGB_TYPE);
		pt.put("R",color.val[2]);
		pt.put("G",color.val[1]);
		pt.put("B",color.val[0]);
	}
	return pt;
}

CvScalar ReadColorFromTree(const wptree& wpt)
{
	CvScalar retColor;
	int color_type = wpt.get<int>(L"type",COLOR_RGB_TYPE);
	if(COLOR_HSV_TYPE == color_type)
	{
		double color_h,color_s,color_v;
		color_h = wpt.get<double>(L"H");
		color_s = wpt.get<double>(L"S");
		color_v = wpt.get<double>(L"V");
		retColor = CV_HSV(color_h,color_s,color_v);
	}
	else
	{
		double color_r,color_g,color_b;
		color_r = wpt.get<double>(L"R");
		color_g = wpt.get<double>(L"G");
		color_b = wpt.get<double>(L"B");
		retColor = CV_RGB(color_r,color_g,color_b);
	}
	return retColor;
}
