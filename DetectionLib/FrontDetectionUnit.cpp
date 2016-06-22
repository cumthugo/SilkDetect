#include "FrontDetectionUnit.hpp"



void FrontDetectionUnit::DetectAlgorithm(const IplImage_Ptr sourceImage ,const CvRect& PedestalRect,DetectionResult& result)
{
	Silk.DetectFlag = ObjectDetectAlgorithm::DETECT_FLAG_APPEAR;
	Silk.Detect(sourceImage,PedestalRect,PedestalPosition,result);
	if(!result.IsPass) return;

	Lock.DetectFlag = ObjectDetectAlgorithm::DETECT_FLAG_DISAPPEAR;
	Lock.Detect(sourceImage,PedestalRect,PedestalPosition,result);
}

ptree FrontDetectionUnit::GetTree() const
{
	ptree pt = DetectionUnit::GetTree();
	pt.put_child("Param.Silk",Silk.GetTree());
	pt.put_child("Param.Lock",Lock.GetTree());
	return pt;
}

void FrontDetectionUnit::ReadFromTree( const wptree& wpt )
{
	DetectionUnit::ReadFromTree(wpt);
	Silk.ReadFromTree(wpt.get_child(L"Param.Silk"));
	Lock.ReadFromTree(wpt.get_child(L"Param.Lock"));
}

bool operator==(const FrontDetectionUnit& lhs, const FrontDetectionUnit& rhs )
{
	return lhs.IsBasicEqual(rhs) && lhs.Lock == rhs.Lock && lhs.Silk == rhs.Silk;
}

bool operator!=(const FrontDetectionUnit& lhs, const FrontDetectionUnit& rhs )
{
	return !(lhs == rhs);
}

ostream& operator<<( ostream& o, const FrontDetectionUnit& rhs )
{
	o << "Front Detection Unit" << endl;
	return o;
}