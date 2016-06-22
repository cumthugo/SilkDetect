#pragma once

#include "DetectionUnit.hpp"

#include "ObjectDetectAlgorithm.hpp"

class BackDetectionUnit : public DetectionUnit
{
protected:
	virtual void DetectAlgorithm(const IplImage_Ptr sourceImage,const CvRect& PedestalRect,DetectionResult& result);
public:
	virtual shared_ptr<DetectionUnit> Clone() const { return shared_ptr<DetectionUnit>(new BackDetectionUnit(*this)); }
	//���л�
public:
	enum {TYPE_ID = 2};
	virtual int GetTypeId() const { return TYPE_ID;}
	virtual ptree GetTree() const;
	virtual void ReadFromTree(const wptree& wpt);
	//����
public:
	CommonSilkDetectAlgorithm BlueBox;
	BackLockDetectAlgorithm Lock;	
};

bool operator==(const BackDetectionUnit& lhs, const BackDetectionUnit& rhs);
bool operator!=(const BackDetectionUnit& lhs, const BackDetectionUnit& rhs);
ostream& operator<<(ostream& o, const BackDetectionUnit& rhs);