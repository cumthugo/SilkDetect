#pragma once

#include "DetectionUnit.hpp"

#include "ObjectDetectAlgorithm.hpp"

class NoLockDetectionUnit : public DetectionUnit
{
protected:
	virtual void DetectAlgorithm(const IplImage_Ptr sourceImage,const CvRect& PedestalRect,DetectionResult& result);
public:
	virtual shared_ptr<DetectionUnit> Clone() const { return shared_ptr<DetectionUnit>(new NoLockDetectionUnit(*this)); }
	//序列化
public:
	enum {TYPE_ID = 4};
	virtual int GetTypeId() const { return TYPE_ID;}
	virtual ptree GetTree() const;
	virtual void ReadFromTree(const wptree& wpt);
	//参数
public:
	CommonSilkDetectAlgorithm Silk;
};


bool operator==(const NoLockDetectionUnit& lhs, const NoLockDetectionUnit& rhs);
bool operator!=(const NoLockDetectionUnit& lhs, const NoLockDetectionUnit& rhs);
ostream& operator<<(ostream& o, const NoLockDetectionUnit& rhs);