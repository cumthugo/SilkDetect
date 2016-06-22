#include "BackDetectionUnit.hpp"



void BackDetectionUnit::DetectAlgorithm( const IplImage_Ptr sourceImage,const CvRect& PedestalRect,DetectionResult& result )
{
	BlueBox.DetectFlag = ObjectDetectAlgorithm::DETECT_FLAG_DISAPPEAR;
	BlueBox.Detect(sourceImage,PedestalRect,PedestalPosition,result);
	if(!result.IsPass) return;
	Lock.DetectFlag = ObjectDetectAlgorithm::DETECT_FLAG_DISAPPEAR;
	Lock.Detect(sourceImage,PedestalRect,PedestalPosition,result);
}

ptree BackDetectionUnit::GetTree() const
{	
	ptree pt = DetectionUnit::GetTree();
	pt.put_child("Param.BlueBox",BlueBox.GetTree());
	pt.put_child("Param.Lock",Lock.GetTree());
	return pt;
}

void BackDetectionUnit::ReadFromTree( const wptree& wpt )
{
	DetectionUnit::ReadFromTree(wpt);
	BlueBox.ReadFromTree(wpt.get_child(L"Param.BlueBox"));
	Lock.ReadFromTree(wpt.get_child(L"Param.Lock"));
}


bool operator==( const BackDetectionUnit& lhs, const BackDetectionUnit& rhs )
{
	return lhs.IsBasicEqual(rhs) && lhs.BlueBox == rhs.BlueBox && lhs.Lock == rhs.Lock;
}

bool operator!=( const BackDetectionUnit& lhs, const BackDetectionUnit& rhs )
{
	return !(lhs == rhs);
}

ostream& operator<<( ostream& o, const BackDetectionUnit& rhs )
{
	o << rhs.Name <<endl;
	return o;
}

