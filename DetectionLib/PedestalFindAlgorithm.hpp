#pragma once

#include "MyLib.hpp"
#include "DetectionResult.hpp"

class PedestalFindAlgorithm : public TreeSerialization
{
public:
	virtual ~PedestalFindAlgorithm(){}
	PedestalFindAlgorithm():XLeastPointNumber(5),YLeastPointNumber(0){}
	virtual CvRect Find(const IplImage_Ptr sourceImage) = 0;

//for test
public:
	virtual bool IsEqual(const shared_ptr<PedestalFindAlgorithm>& rhs) const;
	//序列化
public:
	virtual int GetTypeId() const = 0;
	virtual ptree GetTree() const;
	virtual void ReadFromTree(const wptree& wpt);
	static shared_ptr<PedestalFindAlgorithm> GetFinderFromTree( const wptree& wpt );
protected:
	//内部公共方法
	CvRect DetectObject(const IplImage_Ptr sourceImage);
	void CutBox( const IplImage_Ptr sourceImage, CvRect &box );

	//公共属性
public:
	Range<CvScalar> ColorRange;
	Range<int> SizeRange;
	Range<double> ScaleRange;

	int XLeastPointNumber;
	int YLeastPointNumber;
};


class SimplePedestalFinder : public PedestalFindAlgorithm
{
public:
	int GetTypeId() const { return TYPE_ID;}
	enum { TYPE_ID = 1};
	CvRect Find(const IplImage_Ptr sourceImage);
};

class InclinedPedestalFinder : public PedestalFindAlgorithm
{
public:
	int GetTypeId() const { return TYPE_ID;}
	enum { TYPE_ID = 3};
	CvRect Find(const IplImage_Ptr sourceImage);
protected:
	//内部公共方法
	CvRect DetectObject(const IplImage_Ptr sourceImage);
};

#define DIRECTION_FROM_TOP 1
#define DIRECTION_FROM_BOTTOM 2

class ConstHeightPedestalFinder : public PedestalFindAlgorithm
{
public:
	int GetTypeId() const { return TYPE_ID;}
	enum { TYPE_ID = 2};
	virtual ptree GetTree() const;
	virtual void ReadFromTree(const wptree& wpt);
	CvRect Find(const IplImage_Ptr sourceImage);

//专有属性
public:
	int ReferenceDirection;
	int ExpectHeight;
};