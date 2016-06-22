#include "NoLockDetectionUnit.hpp"

void NoLockDetectionUnit::DetectAlgorithm( const IplImage_Ptr sourceImage,const CvRect& PedestalRect,DetectionResult& result )
{
	Clock_MS cl;
	cl.Start();
	Silk.DetectFlag = ObjectDetectAlgorithm::DETECT_FLAG_APPEAR;
	Silk.Detect(sourceImage,PedestalRect,PedestalPosition,result);
	cl.Stop();
	result.AddItemReport(this->Name,"Silk",result.IsPass(),cl.GetTime());
}

ptree NoLockDetectionUnit::GetTree() const
{
	ptree pt = DetectionUnit::GetTree();
	pt.put_child("Param.Silk",Silk.GetTree());
	return pt;
}

void NoLockDetectionUnit::ReadFromTree( const wptree& wpt )
{
	DetectionUnit::ReadFromTree(wpt);
	Silk.ReadFromTree(wpt.get_child(L"Param.Silk"));
}

bool operator==( const NoLockDetectionUnit& lhs, const NoLockDetectionUnit& rhs )
{
	return lhs.IsBasicEqual(rhs)  && lhs.Silk == rhs.Silk;
}

bool operator!=( const NoLockDetectionUnit& lhs, const NoLockDetectionUnit& rhs )
{
	return !(lhs == rhs);
}

ostream& operator<<( ostream& o, const NoLockDetectionUnit& rhs )
{
	o << "No Lock Detection Unit" << endl;
	return o;
}
