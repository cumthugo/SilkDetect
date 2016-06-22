#pragma once

#include "MyLib.hpp"
#include "DetectionResult.hpp"

class ObjectDetectAlgorithm : public TreeSerialization
{
public:
	virtual ~ObjectDetectAlgorithm(){}
	virtual void Detect(const IplImage_Ptr sourceImage,const CvRect& PedestalRect,int PedestalPosition, DetectionResult& result ) = 0;
public:
	enum DETECTFLAG { DETECT_FLAG_APPEAR = 0, DETECT_FLAG_DISAPPEAR = 1};
protected:
	enum ScanDirection { SCAN_FROM_BOTTOM = 0, SCAN_FROM_TOP = 1};
	
	int ObjectChangePosition(const IplImage_Ptr sourceImage, const CvRect& detectRect, const Range<CvScalar>& colorRange,int objectWidth, int scanDirection = SCAN_FROM_BOTTOM, int detectFlag = DETECT_FLAG_APPEAR);
	bool isObjectInRect(const IplImage_Ptr sourceImage, const CvRect& detectRect, const Range<CvScalar>& colorRange,int objectWidth, int scanDirection = SCAN_FROM_BOTTOM, int detectFlag = DETECT_FLAG_APPEAR);
};


class SilkDetectAlgorithm : public ObjectDetectAlgorithm
{
public:
	virtual void Detect(const IplImage_Ptr sourceImage,const CvRect& PedestalRect,int PedestalPosition,DetectionResult& result ) = 0;
};

class LockDetectAlgorithm : public ObjectDetectAlgorithm
{
public:
	virtual void Detect(const IplImage_Ptr sourceImage,const CvRect& PedestalRect,int PedestalPosition,DetectionResult& result ) = 0;
};


class CommonSilkDetectAlgorithm : public SilkDetectAlgorithm
{
public:
	CommonSilkDetectAlgorithm():XOffset(0),SearchWidth(0),MaxGapAround(-1){}
	void Detect(const IplImage_Ptr sourceImage,const CvRect& PedestalRect,int PedestalPosition,DetectionResult& result );
	//序列化
public:
	virtual ptree GetTree() const;
	virtual void ReadFromTree(const wptree& wpt);
public:
	DETECTFLAG DetectFlag;
	//Silk
	Range<CvScalar> ColorRange;
	Range<int> SearchRange;
	int PixelCount;
	int XOffset;
	int SearchWidth;
	int MaxGapAround;
};

bool operator==(const CommonSilkDetectAlgorithm& lhs, const CommonSilkDetectAlgorithm& rhs);
bool operator!=(const CommonSilkDetectAlgorithm& lhs, const CommonSilkDetectAlgorithm& rhs);
ostream& operator<<(ostream& o, const CommonSilkDetectAlgorithm& rhs);


class FrontLockDetectAlgorithm : public LockDetectAlgorithm
{
public:
	void Detect(const IplImage_Ptr sourceImage,const CvRect& PedestalRect,int PedestalPosition,DetectionResult& result );
	//序列化
public:
	virtual ptree GetTree() const;
	virtual void ReadFromTree(const wptree& wpt);
public:
	DETECTFLAG DetectFlag;
	//Lock
	Range<CvScalar> ColorRange;
	Range<int> SearchRange;
	int PixelCount;
	int XOffset;
	int SearchWidth;
};
bool operator==(const FrontLockDetectAlgorithm& lhs, const FrontLockDetectAlgorithm& rhs);
bool operator!=(const FrontLockDetectAlgorithm& lhs, const FrontLockDetectAlgorithm& rhs);
ostream& operator<<(ostream& o, const FrontLockDetectAlgorithm& rhs);



class BackLockDetectAlgorithm : public LockDetectAlgorithm
{
public:
	void Detect(const IplImage_Ptr sourceImage,const CvRect& PedestalRect,int PedestalPosition,DetectionResult& result );
	//序列化
public:
	virtual ptree GetTree() const;
	virtual void ReadFromTree(const wptree& wpt);
public:
	DETECTFLAG DetectFlag;
	//Lock
	Range<CvScalar> ColorRange;
	Range<int> SearchRange;
	int PixelCount;
};
bool operator==(const BackLockDetectAlgorithm& lhs, const BackLockDetectAlgorithm& rhs);
bool operator!=(const BackLockDetectAlgorithm& lhs, const BackLockDetectAlgorithm& rhs);
ostream& operator<<(ostream& o, const BackLockDetectAlgorithm& rhs);




