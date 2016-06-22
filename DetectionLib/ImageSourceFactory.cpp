#include "ImageSourceFactory.hpp"

#include "UC_3000.hpp"

shared_ptr<ImageSource> ImageSourceFactory::GetImageFromFile( const string& FileName )
{
	return shared_ptr<ImageSource>();
}

shared_ptr<ImageSource> ImageSourceFactory::GetImageFromCamera()
{
	static shared_ptr<ImageSource> camera_image_source;
	if(!camera_image_source)
		camera_image_source = shared_ptr<ImageSource>(new UC_3000);
	return camera_image_source;
}	
