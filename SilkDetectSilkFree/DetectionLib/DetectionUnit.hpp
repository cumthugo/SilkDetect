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

	//�������㷨
	shared_ptr<PedestalFindAlgorithm> PedestalFinder;

public:
	virtual shared_ptr<DetectionUnit> Clone() const= 0;
	//���л�
public:
	virtual int GetTypeId() const = 0;
	virtual ptree GetTree() const;
	virtual void ReadFromTree(const wptree& wpt);
public:
	CvRect SubImageRect;
	//Position
	int PedestalPosition;
	int PreProcess; //Ԥ����
	int NeedRotate90; //���ڼ�ⴹֱ�����ϵ�����,����˳ʱ����ת added 2.1.11 2014/1/16

protected:
	enum ScanDirection { SCAN_FROM_BOTTOM = 0, SCAN_FROM_TOP = 1};
	enum { DETECT_FLAG_APPEAR = 0, DETECT_FLAG_DISAPPEAR = 1};
	
	DetectionUnit():SubImageRect(cvRect(0,0,0,0)),PreProcess(0),NeedRotate90(0),PedestalPosition(SCAN_FROM_BOTTOM){}
	DetectionUnit(const string& Name):NamedItem(Name),SubImageRect(cvRect(0,0,0,0)),PreProcess(0),NeedRotate90(0),PedestalPosition(SCAN_FROM_BOTTOM){}
	virtual void DetectAlgorithm(const IplImage_Ptr sourceImage,const CvRect& PedestalRect,DetectionResult& result) = 0;
};
