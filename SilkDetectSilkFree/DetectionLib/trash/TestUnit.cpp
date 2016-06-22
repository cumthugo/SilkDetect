#include "TestUnit.hpp"



ptree TestUnit::GetTree() const
{
	ptree pt = NamedItem::GetTree();

	pt.put("IsEnable",IsEnable);
	pt.put("PreProcessing",PreProcessing);
	pt.put("SubRect.x",SubRect.x);
	pt.put("SubRect.y",SubRect.y);
	pt.put("SubRect.width",SubRect.width);
	pt.put("SubRect.height",SubRect.height);

	pt.put("PedestalDetectionCondition.Color.Min.R",PedestalDetectionCondition.ColorRange.Min().val[2]);
	pt.put("PedestalDetectionCondition.Color.Min.G",PedestalDetectionCondition.ColorRange.Min().val[1]);
	pt.put("PedestalDetectionCondition.Color.Min.B",PedestalDetectionCondition.ColorRange.Min().val[0]);
	pt.put("PedestalDetectionCondition.Color.Max.R",PedestalDetectionCondition.ColorRange.Max().val[2]);
	pt.put("PedestalDetectionCondition.Color.Max.G",PedestalDetectionCondition.ColorRange.Max().val[1]);
	pt.put("PedestalDetectionCondition.Color.Max.B",PedestalDetectionCondition.ColorRange.Max().val[0]);
	pt.put("PedestalDetectionCondition.Scale.Min",PedestalDetectionCondition.ScaleRange.Min());
	pt.put("PedestalDetectionCondition.Scale.Max",PedestalDetectionCondition.ScaleRange.Max());
	pt.put("PedestalDetectionCondition.Length.Min",PedestalDetectionCondition.LengthRange.Min());
	pt.put("PedestalDetectionCondition.Length.Max",PedestalDetectionCondition.LengthRange.Max());

	pt.put("SilkDetectionCondition.Color.Min.R",SilkDetectionCondition.ColorRange.Min().val[2]);
	pt.put("SilkDetectionCondition.Color.Min.G",SilkDetectionCondition.ColorRange.Min().val[1]);
	pt.put("SilkDetectionCondition.Color.Min.B",SilkDetectionCondition.ColorRange.Min().val[0]);
	pt.put("SilkDetectionCondition.Color.Max.R",SilkDetectionCondition.ColorRange.Max().val[2]);
	pt.put("SilkDetectionCondition.Color.Max.G",SilkDetectionCondition.ColorRange.Max().val[1]);
	pt.put("SilkDetectionCondition.Color.Max.B",SilkDetectionCondition.ColorRange.Max().val[0]);
	pt.put("SilkDetectionCondition.Scale.Min",SilkDetectionCondition.ScaleRange.Min());
	pt.put("SilkDetectionCondition.Scale.Max",SilkDetectionCondition.ScaleRange.Max());
	pt.put("SilkDetectionCondition.Length.Min",SilkDetectionCondition.LengthRange.Min());
	pt.put("SilkDetectionCondition.Length.Max",SilkDetectionCondition.LengthRange.Max());

	pt.put("LockDetectionCondition.Color.Min.R",LockDetectionCondition.ColorRange.Min().val[2]);
	pt.put("LockDetectionCondition.Color.Min.G",LockDetectionCondition.ColorRange.Min().val[1]);
	pt.put("LockDetectionCondition.Color.Min.B",LockDetectionCondition.ColorRange.Min().val[0]);
	pt.put("LockDetectionCondition.Color.Max.R",LockDetectionCondition.ColorRange.Max().val[2]);
	pt.put("LockDetectionCondition.Color.Max.G",LockDetectionCondition.ColorRange.Max().val[1]);
	pt.put("LockDetectionCondition.Color.Max.B",LockDetectionCondition.ColorRange.Max().val[0]);
	pt.put("LockDetectionCondition.Scale.Min",LockDetectionCondition.ScaleRange.Min());
	pt.put("LockDetectionCondition.Scale.Max",LockDetectionCondition.ScaleRange.Max());
	pt.put("LockDetectionCondition.Length.Min",LockDetectionCondition.LengthRange.Min());
	pt.put("LockDetectionCondition.Length.Max",LockDetectionCondition.LengthRange.Max());

	pt.put("DistancePedestalToSilk.Min",DistancePedestalToSilk.Min());
	pt.put("DistancePedestalToSilk.Max",DistancePedestalToSilk.Max());



	pt.put("MaxTolerance",MaxTolerance);
	pt.put("DistancePedestalToLock.Min",DistancePedestalToLock.Min());
	pt.put("DistancePedestalToLock.Max",DistancePedestalToLock.Max());

	return pt;


}

void TestUnit::ReadFromTree( const wptree& wpt )
{
	NamedItem::ReadFromTree(wpt);
	wstring temp;

	IsEnable = wpt.get<bool>(L"IsEnable");
	PreProcessing = wpt.get<int>(L"PreProcessing");
	SubRect.x = wpt.get<int>(L"SubRect.x");
	SubRect.y = wpt.get<int>(L"SubRect.y");
	SubRect.width = wpt.get<int>(L"SubRect.width");
	SubRect.height = wpt.get<int>(L"SubRect.height");


	double color_r,color_g,color_b;
	CvScalar color_from,color_to;
	double scale_from,scale_to;
	int length_from,length_to;

	color_r = wpt.get<double>(L"PedestalDetectionCondition.Color.Min.R");
	color_g = wpt.get<double>(L"PedestalDetectionCondition.Color.Min.G");
	color_b = wpt.get<double>(L"PedestalDetectionCondition.Color.Min.B");
	color_from = CV_RGB(color_r,color_g,color_b);
	color_r = wpt.get<double>(L"PedestalDetectionCondition.Color.Max.R");
	color_g = wpt.get<double>(L"PedestalDetectionCondition.Color.Max.G");
	color_b = wpt.get<double>(L"PedestalDetectionCondition.Color.Max.B");
	color_to = CV_RGB(color_r,color_g,color_b);
	scale_from = wpt.get<double>(L"PedestalDetectionCondition.Scale.Min");
	scale_to = wpt.get<double>(L"PedestalDetectionCondition.Scale.Max");
	length_from = wpt.get<int>(L"PedestalDetectionCondition.Length.Min");
	length_to = wpt.get<int>(L"PedestalDetectionCondition.Length.Max");
	PedestalDetectionCondition.ColorRange = Range<CvScalar>(color_from,color_to);
	PedestalDetectionCondition.ScaleRange = Range<double>(scale_from,scale_to);
	PedestalDetectionCondition.LengthRange = Range<int>(length_from,length_to);


	color_r = wpt.get<double>(L"SilkDetectionCondition.Color.Min.R");
	color_g = wpt.get<double>(L"SilkDetectionCondition.Color.Min.G");
	color_b = wpt.get<double>(L"SilkDetectionCondition.Color.Min.B");
	color_from = CV_RGB(color_r,color_g,color_b);
	color_r = wpt.get<double>(L"SilkDetectionCondition.Color.Max.R");
	color_g = wpt.get<double>(L"SilkDetectionCondition.Color.Max.G");
	color_b = wpt.get<double>(L"SilkDetectionCondition.Color.Max.B");
	color_to = CV_RGB(color_r,color_g,color_b);
	scale_from = wpt.get<double>(L"SilkDetectionCondition.Scale.Min");
	scale_to = wpt.get<double>(L"SilkDetectionCondition.Scale.Max");
	length_from = wpt.get<int>(L"SilkDetectionCondition.Length.Min");
	length_to = wpt.get<int>(L"SilkDetectionCondition.Length.Max");
	SilkDetectionCondition.ColorRange = Range<CvScalar>(color_from,color_to);
	SilkDetectionCondition.ScaleRange = Range<double>(scale_from,scale_to);
	SilkDetectionCondition.LengthRange = Range<int>(length_from,length_to);


	color_r = wpt.get<double>(L"LockDetectionCondition.Color.Min.R");
	color_g = wpt.get<double>(L"LockDetectionCondition.Color.Min.G");
	color_b = wpt.get<double>(L"LockDetectionCondition.Color.Min.B");
	color_from = CV_RGB(color_r,color_g,color_b);
	color_r = wpt.get<double>(L"LockDetectionCondition.Color.Max.R");
	color_g = wpt.get<double>(L"LockDetectionCondition.Color.Max.G");
	color_b = wpt.get<double>(L"LockDetectionCondition.Color.Max.B");
	color_to = CV_RGB(color_r,color_g,color_b);
	scale_from = wpt.get<double>(L"LockDetectionCondition.Scale.Min");
	scale_to = wpt.get<double>(L"LockDetectionCondition.Scale.Max");
	length_from = wpt.get<int>(L"LockDetectionCondition.Length.Min");
	length_to = wpt.get<int>(L"LockDetectionCondition.Length.Max");

	LockDetectionCondition.ColorRange = Range<CvScalar>(color_from,color_to);
	LockDetectionCondition.ScaleRange = Range<double>(scale_from,scale_to);
	LockDetectionCondition.LengthRange = Range<int>(length_from,length_to);

	
	int distance_from,distance_to;
	distance_from = wpt.get<int>(L"DistancePedestalToSilk.Min");
	distance_to = wpt.get<int>(L"DistancePedestalToSilk.Max");
	DistancePedestalToSilk = Range<int>(distance_from,distance_to);

	MaxTolerance = wpt.get<int>(L"MaxTolerance");

	distance_from = wpt.get<int>(L"DistancePedestalToLock.Min");
	distance_to = wpt.get<int>(L"DistancePedestalToLock.Max");
	DistancePedestalToLock = Range<int>(distance_from,distance_to);
	
}

bool operator==( const TestUnit& lhs, const TestUnit& rhs )
{
	return lhs.Name == rhs.Name &&
		lhs.IsEnable == rhs.IsEnable &&
		lhs.SubRect == rhs.SubRect &&
		lhs.PedestalDetectionCondition == rhs.PedestalDetectionCondition &&
		lhs.SilkDetectionCondition == rhs.SilkDetectionCondition &&
		lhs.LockDetectionCondition == rhs.LockDetectionCondition &&
		lhs.DistancePedestalToSilk == rhs.DistancePedestalToSilk &&
		lhs.MaxTolerance == rhs.MaxTolerance &&
		lhs.DistancePedestalToLock == rhs.DistancePedestalToLock;
}

bool operator!=( const TestUnit& lhs, const TestUnit& rhs )
{
	return !(lhs == rhs);
}

ostream& operator<<( ostream& o, const TestUnit& rhs )
{
	o   << "\nTestUnit: Name:" << rhs.Name
			<< "\n  Enable:" << rhs.IsEnable
			<< "\n  SubRect: " << rhs.SubRect
			<< "\n  PedestalDetectionCondition: " << rhs.PedestalDetectionCondition
			<< "\n  SilkDetectionCondition: " << rhs.SilkDetectionCondition
			<< "\n  LockDetectionCondition: " << rhs.LockDetectionCondition
			<< "\n  DistancePedestalToSilk: " << rhs.DistancePedestalToSilk
			<< "\n  MaxTolerance: " << rhs.MaxTolerance
			<< "\n  DistancePedestalToLock: " << rhs.DistancePedestalToLock;
	return o;
}


bool operator==(const ObjectDetectionCondition& lhs, const ObjectDetectionCondition& rhs)
{
	return lhs.ColorRange == rhs.ColorRange && lhs.ScaleRange == rhs.ScaleRange && lhs.LengthRange == rhs.LengthRange;
}
bool operator!=(const ObjectDetectionCondition& lhs, const ObjectDetectionCondition& rhs)
{
	return !(lhs==rhs);
}
ostream& operator<<(ostream& o, const ObjectDetectionCondition& rhs)
{
	o << "\n    Color: " << rhs.ColorRange << "\n    Scale: " << rhs.ScaleRange << "\n    Length: " << rhs.LengthRange;
	return o;
}


