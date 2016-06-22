#include "HardLockDetectionUnit.hpp"
void HardLockDetectionUnit::DetectAlgorithm( const IplImage_Ptr sourceImage,const CvRect& PedestalRect,DetectionResult& result )
{
	/**/Silk.DetectFlag = ObjectDetectAlgorithm::DETECT_FLAG_APPEAR;
	Silk.Detect(sourceImage,PedestalRect,PedestalPosition,result);
	if(!result.IsPass) return;
	
	Lock.DetectFlag = ObjectDetectAlgorithm::DETECT_FLAG_APPEAR;
	Lock.Detect(sourceImage,PedestalRect,PedestalPosition,result);
}

ptree HardLockDetectionUnit::GetTree() const
{
	ptree pt = DetectionUnit::GetTree();
	pt.put_child("Param.Silk",Silk.GetTree());
	pt.put_child("Param.Lock",Lock.GetTree());
	return pt;
}

void HardLockDetectionUnit::ReadFromTree( const wptree& wpt )
{
	DetectionUnit::ReadFromTree(wpt);
	Silk.ReadFromTree(wpt.get_child(L"Param.Silk"));
	Lock.ReadFromTree(wpt.get_child(L"Param.Lock"));
}

bool operator==( const HardLockDetectionUnit& lhs, const HardLockDetectionUnit& rhs )
{
	return lhs.IsBasicEqual(rhs) && lhs.Lock == rhs.Lock && lhs.Silk == rhs.Silk;
}

bool operator!=( const HardLockDetectionUnit& lhs, const HardLockDetectionUnit& rhs )
{
	return !(lhs == rhs);
}

ostream& operator<<( ostream& o, const HardLockDetectionUnit& rhs )
{
	o << "Hard Lock Detection Unit!" << endl;
	return o;
}
