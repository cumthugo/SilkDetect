#pragma once

#include "ImageSource.hpp"

class UC_3000 : public ImageSource
{
public:
	UC_3000();
	virtual IplImage_Ptr GetImage() const;
};

