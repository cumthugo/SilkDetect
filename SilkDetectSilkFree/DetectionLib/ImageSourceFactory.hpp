#pragma once

#include "ImageSource.hpp"


class ImageSourceFactory
{
public:
	static shared_ptr<ImageSource> GetImageFromFile(const string& FileName);
	static shared_ptr<ImageSource> GetImageFromCamera();
};