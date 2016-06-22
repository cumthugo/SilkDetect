#pragma once

#include "MyLib.hpp"

#include "DetectionResult.hpp"
#include "PedestalFindAlgorithm.hpp"

class DetectionUnit : public NamedItem
{
public:
	virtual ~DetectionUnit(){}
	void Detect(IplImage_Ptr sourceImage,DetectionResult& result);
	bool IsBasicEqual(const DetectionUnit& rhs) const;

	//¼ì²âµ××ùËã·¨
	shared_ptr<PedestalFindAlgorithm> PedestalFinder;

public:
	virtual shared_ptr<DetectionUnit> Clone() const= 0;
	//ÐòÁÐ»¯
public:
	virtual int GetTypeId() const = 0;
	virtual ptree GetTree() const;
	virtual void ReadFromTree(const wptree& wpt);
public:
	CvRect SubImageRect;
	//Position
	int PedestalPosition;

protected:
	enum ScanDirection { SCAN_FROM_BOTTOM = 0, SCAN_FROM_TOP = 1};
	enum { DETECT_FLAG_APPEAR = 0, DETECT_FLAG_DISAPPEAR = 1};
	CvRect DetectObject(const IplImage_Ptr sourceImage,const Range<CvScalar>& colorRange, const Range<double>& scaleRange, const Range<int>& sizeRange);
	
	DetectionUnit():SubImageRect(cvRect(0,0,0,0)){}
	DetectionUnit(const string& Name):NamedItem(Name),SubImageRect(cvRect(0,0,0,0)){}
	virtual void DetectAlgorithm(const IplImage_Ptr sourceImage,const CvRect& PedestalRect,DetectionResult& result) = 0;
};
