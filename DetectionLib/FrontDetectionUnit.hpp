#pragma once

#include "DetectionUnit.hpp"

#include "ObjectDetectAlgorithm.hpp"

class FrontDetectionUnit : public DetectionUnit
{
protected:
	virtual void DetectAlgorithm(const IplImage_Ptr sourceImage,const CvRect& PedestalRect,DetectionResult& result);
public:	
	virtual shared_ptr<DetectionUnit> Clone() const { return shared_ptr<DetectionUnit>(new FrontDetectionUnit(*this)); }
	//序列化
public:
	enum {TYPE_ID = 1};
	virtual int GetTypeId() const { return TYPE_ID;}
	virtual ptree GetTree() const;
	virtual void ReadFromTree(const wptree& wpt);
//参数
public:
	CommonSilkDetectAlgorithm Silk;
	FrontLockDetectAlgorithm Lock;
};


bool operator==(const FrontDetectionUnit& lhs, const FrontDetectionUnit& rhs);
bool operator!=(const FrontDetectionUnit& lhs, const FrontDetectionUnit& rhs);
ostream& operator<<(ostream& o, const FrontDetectionUnit& rhs);