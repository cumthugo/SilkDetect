#include "RotateAlgorithm.hpp"



void RotateAlgorithm::DetectAlgorithm( const IplImage_Ptr sourceImage ,DetectionResult& result)
{
	IplImage_Ptr rotateImage = cvCreateImage(cvGetSize(sourceImage),sourceImage->depth,sourceImage->nChannels);
	Rotating180(sourceImage,rotateImage);
	cvCopy(rotateImage,result.ResultImage);
	itsOrignAlgorithm->DetectAlgorithm(rotateImage,result);
	Rotating180(result.ResultImage,result.ResultImage);
}