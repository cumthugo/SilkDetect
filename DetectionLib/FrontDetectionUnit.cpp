#include "FrontDetectionUnit.hpp"



void FrontDetectionUnit::DetectAlgorithm(const IplImage_Ptr sourceImage ,const CvRect& PedestalRect,DetectionResult& result)
{
	Clock_MS cl;
	cl.Start();
	Silk.DetectFlag = ObjectDetectAlgorithm::DETECT_FLAG_APPEAR;
	Silk.Detect(sourceImage,PedestalRect,PedestalPosition,result);
	cl.Stop();
	result.AddItemReport(this->Name,"Ë¿Ó¡",result.IsPass(),cl.GetTime());
	
	if(!result.IsPass()) return;
	cl.Start();
	Lock.DetectFlag = ObjectDetectAlgorithm::DETECT_FLAG_DISAPPEAR;
	Lock.Detect(sourceImage,PedestalRect,PedestalPosition,result);
	cl.Stop();
	result.AddItemReport(this->Name,"Ëø¿Û",result.IsPass(),cl.GetTime());
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