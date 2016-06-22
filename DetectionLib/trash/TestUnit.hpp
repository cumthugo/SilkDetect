#pragma once

#include "MyLib.hpp"

class ObjectDetectionCondition
{
public:
	Range<CvScalar> ColorRange;
	Range<double> ScaleRange;	// range for (long div short)
	Range<int> LengthRange;		// range for long size	 
};

bool operator==(const ObjectDetectionCondition& lhs, const ObjectDetectionCondition& rhs);
bool operator!=(const ObjectDetectionCondition& lhs, const ObjectDetectionCondition& rhs);
ostream& operator<<(ostream& o, const ObjectDetectionCondition& rhs);





class TestUnit : public NamedItem
{
public:
	//constructor
	TestUnit():PreProcessing(0),MaxTolerance(-1),IsEnable(false){}
	TestUnit(const string& UnitName, bool enable = false):PreProcessing(0),MaxTolerance(-1),NamedItem(UnitName),IsEnable(enable){}


	//ÐòÁÐ»¯
	virtual ptree GetTree() const;
	virtual void ReadFromTree(const wptree& wpt);

	//ÊôÐÔ
	bool IsEnable;
	CvRect SubRect;
	int PreProcessing; // 0 for not process, 1 for process Equalize Hist
	// object detection
	ObjectDetectionCondition PedestalDetectionCondition;
	ObjectDetectionCondition SilkDetectionCondition;
	ObjectDetectionCondition LockDetectionCondition;
	// condition
	Range<int> DistancePedestalToSilk; // the distance between pedestal and silk
	int MaxTolerance; //the left and the right tolerance
	Range<int> DistancePedestalToLock;
};


bool operator==(const TestUnit& lhs, const TestUnit& rhs);
bool operator!=(const TestUnit& lhs, const TestUnit& rhs);
ostream& operator<<(ostream& o, const TestUnit& rhs);


