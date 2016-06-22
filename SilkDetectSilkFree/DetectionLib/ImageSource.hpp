#pragma once

#include "MyLib.hpp"

class ImageSource
{
public:
	virtual IplImage_Ptr GetImage() const = 0;
	virtual ~ImageSource(){}
};