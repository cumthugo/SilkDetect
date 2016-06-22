#include "DetectionUnit.hpp"


void DetectionUnit::Detect(IplImage_Ptr sourceImage,DetectionResult& result)
{
	Clock_MS cl;
	cl.Start();	
	result.ErrorCode = RESULT_PASS;	
	assert(PedestalFinder);
	//rotate if need
	if(NeedRotate90)
		sourceImage = Rotate90Clockwise(sourceImage);
	if(PreProcess)
		PedestalFinder->ProcessInclined(sourceImage);

	result.ResultImage = cvCloneImage(sourceImage);
	cl.Stop();

	//上面过程为预处理，可以将至输出到报告中	
	result.AddItemReport(this->Name,"预处理",true,cl.GetTime());

	cl.Start();
	CvRect FindPedestalRect = PedestalFinder->Find(sourceImage);
	bool IsFindPedestal = (FindPedestalRect.width != 0);	
	cl.Stop();
	result.AddItemReport(this->Name,"插座",IsFindPedestal,cl.GetTime());

	if(!IsFindPedestal)
	{			
		result.ErrorCode = RESULT_FAIL_PEDESTAL;
		cvAddS(result.ResultImage,CV_RGB(100,0,0),result.ResultImage);
		if(NeedRotate90)
			result.ResultImage = Rotate90CounterClockwise(result.ResultImage);
		return;
	}

	FillRect(result.ResultImage,FindPedestalRect,CV_RGB(100,100,0));

	//add cable detect
	cl.Start();
	CableDetector.Detect(sourceImage,FindPedestalRect,PedestalPosition,result);
	cl.Stop();
	result.AddItemReport(this->Name,"排线插入",result.IsPass(),cl.GetTime());

	if(result.IsPass())
		DetectAlgorithm(sourceImage,FindPedestalRect,result);

	//if rotate, rotate result
	if(NeedRotate90)
		result.ResultImage = Rotate90CounterClockwise(result.ResultImage);
}

ptree DetectionUnit::GetTree() const
{
	ptree pt =  NamedItem::GetTree();
	pt.put("Type",GetTypeId());
	pt.put("Param.SubRect.x",SubImageRect.x);
	pt.put("Param.SubRect.y",SubImageRect.y);
	pt.put("Param.SubRect.width",SubImageRect.width);
	pt.put("Param.SubRect.height",SubImageRect.height);

	pt.put("Param.PedestalPosition",PedestalPosition);
	pt.put("Param.PreProcess",PreProcess);
	pt.put("Param.NeedRotate90",NeedRotate90);		//add 2.1.11
	pt.put_child("Param.Pedestal",PedestalFinder->GetTree());

	pt.put_child("Param.Cable",CableDetector.GetTree()); //add 2.2.2 2014/7/28
	return pt;
}

void DetectionUnit::ReadFromTree( const wptree& wpt )
{
	using boost::property_tree::ptree_bad_path;
	NamedItem::ReadFromTree(wpt);
	SubImageRect.x = wpt.get<int>(L"Param.SubRect.x");
	SubImageRect.y = wpt.get<int>(L"Param.SubRect.y");
	SubImageRect.width = wpt.get<int>(L"Param.SubRect.width");
	SubImageRect.height = wpt.get<int>(L"Param.SubRect.height");

	PedestalPosition = wpt.get<int>(L"Param.PedestalPosition",PEDESTAL_ON_BOTTOM);
	PreProcess = wpt.get<int>(L"Param.PreProcess",0);	
	NeedRotate90 = wpt.get<int>(L"Param.NeedRotate90",0);	//add 2.1.11

	PedestalFinder = PedestalFindAlgorithm::GetFinderFromTree(wpt.get_child(L"Param.Pedestal"));

	try
	{
		CableDetector.ReadFromTree(wpt.get_child(L"Param.Cable"));
	}
	catch(ptree_bad_path&)	//should use default value for update
	{
		CableDetector.ColorRange = Range<CvScalar>(CV_RGB(0,0,0),CV_RGB(255,255,255));		
		CableDetector.SearchRange = Range<int>(0,0);
		CableDetector.PixelCount = 0;
		CableDetector.XOffset = 0;
		CableDetector.SearchWidth = 0;
	}
}

bool DetectionUnit::IsBasicEqual( const DetectionUnit& rhs ) const
{
	return Name == rhs.Name && SubImageRect == rhs.SubImageRect && 
		PedestalPosition == rhs.PedestalPosition && PreProcess == rhs.PreProcess && NeedRotate90 == rhs.NeedRotate90 && PedestalFinder->IsEqual(rhs.PedestalFinder);
}
