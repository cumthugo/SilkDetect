#pragma once

#include "DetectionUnit.hpp"

#include "ObjectDetectAlgorithm.hpp"

class HardLockDetectionUnit : public DetectionUnit
{
protected:
	virtual void DetectAlgorithm(const IplImage_Ptr sourceImage,const CvRect& PedestalRect,DetectionResult& result);
public:	
	virtual shared_ptr<DetectionUnit> Clone() const { return shared_ptr<DetectionUnit>(new HardLockDetectionUnit(*this)); }
	//序列化
public:
	enum {TYPE_ID = 3};
	virtual int GetTypeId() const { return TYPE_ID;}
	virtual ptree GetTree() const;
	virtual void ReadFromTree(const wptree& wpt);

	//参数
public:
	CommonSilkDetectAlgorithm Silk;
	FrontLockDetectAlgorithm Lock;	
};

bool operator==(const HardLockDetectionUnit& lhs, const HardLockDetectionUnit& rhs);
bool operator!=(const HardLockDetectionUnit& lhs, const HardLockDetectionUnit& rhs);
ostream& operator<<(ostream& o, const HardLockDetectionUnit& rhs);