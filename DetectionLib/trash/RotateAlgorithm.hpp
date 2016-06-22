#include "DetectionAlgorithm.hpp"



class RotateAlgorithm : public DetectionAlgorithm
{
public:
	RotateAlgorithm(const shared_ptr<DetectionAlgorithm>& orignAlgorithm):DetectionAlgorithm(orignAlgorithm->SubImageRect),itsOrignAlgorithm(orignAlgorithm){}
	virtual void DetectAlgorithm(const IplImage_Ptr sourceImage,DetectionResult& result);
private:
	shared_ptr<DetectionAlgorithm> itsOrignAlgorithm;
};