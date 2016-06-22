#include <cppunit/config/SourcePrefix.h>

#include "test.h"


#include "../DetectionLib/MyLib.hpp"

#include "../DetectionLib/FrontDetectionUnit.hpp"
#include "../DetectionLib/DetectionProgram.hpp"
#include "../DetectionLib/DetectionLine.hpp"
#include "../DetectionLib/BackDetectionUnit.hpp"
#include "../DetectionLib/HardLockDetectionUnit.hpp"
#include "../DetectionLib/DetectionUnitFactory.hpp"

#include "../DetectionLib/PedestalFindAlgorithm.hpp"

#include "../DetectionLib/md5.h"

#include <fstream>

#ifdef _DEBUG
#pragma comment(lib,"cxcore200d.lib")
#pragma comment(lib,"cv200d.lib")
#pragma comment(lib,"highgui200d.lib")
#else
#pragma comment(lib,"cxcore200.lib")
#pragma comment(lib,"cv200.lib")
#pragma comment(lib,"highgui200.lib")
#endif


CPPUNIT_TEST_SUITE_REGISTRATION(Test);


//void Test::setUp()
//{
//	
//}

void Test::Test_RestrictRect()
{
	CvRect test1(cvRect(0,0,1,1));
	RestrictRect(test1,cvRect(0,0,1,1));
	CPPUNIT_ASSERT_EQUAL(cvRect(0,0,1,1),test1);
	RestrictRect(test1,cvRect(0,0,100,20));
	CPPUNIT_ASSERT_EQUAL(cvRect(0,0,1,1),test1);
	
	CvRect test2(cvRect(0,0,1,1));
	RestrictRect(test2,cvRect(1,1,1,1));
	CPPUNIT_ASSERT_EQUAL(cvRect(1,1,1,1),test2);

	CvRect test3(cvRect(0,0,2,2));
	RestrictRect(test3,cvRect(0,0,1,1));
	CPPUNIT_ASSERT_EQUAL(cvRect(0,0,1,1),test3);

	CvRect test4(cvRect(50,30,60,80));
	RestrictRect(test4,cvRect(0,0,100,100));
	CPPUNIT_ASSERT_EQUAL(cvRect(40,20,60,80),test4);

	CvRect test5(cvRect(50,30,200,200));
	RestrictRect(test5,cvRect(0,0,100,100));
	CPPUNIT_ASSERT_EQUAL(cvRect(0,0,100,100),test5);


	CvRect test6(cvRect(200,300,10,10));
	RestrictRect(test6,cvRect(0,0,100,100));
	CPPUNIT_ASSERT_EQUAL(cvRect(90,90,10,10),test6);
}

void print_name(const NamedItem& nt)
{
	cout << nt.Name << endl;
}



void Test::Test_UnitSerialization()
{
	wptree pt_read;
	CvScalar color_HSV = CV_HSV(10,11,12);
	write_xml("./hsv_color.xml",GetColorTree(color_HSV));
	read_xml("./hsv_color.xml",pt_read);

	CvScalar read_color = ReadColorFromTree(pt_read);
	CPPUNIT_ASSERT_EQUAL(color_HSV,read_color);

	CvScalar color_RGB = CV_RGB(21,22,23);
	write_xml("./rgb_color.xml",GetColorTree(color_RGB));
	read_xml("./rgb_color.xml",pt_read);
	read_color = ReadColorFromTree(pt_read);
	CPPUNIT_ASSERT_EQUAL(color_RGB,read_color);




	shared_ptr<FrontDetectionUnit> fdu(new FrontDetectionUnit);
	fdu->Name = "FrontUnit";
	fdu->SubImageRect = cvRect(1,2,3,4);
	fdu->PedestalPosition = PEDESTAL_ON_BOTTOM;
	fdu->PedestalFinder = shared_ptr<PedestalFindAlgorithm>(new SimplePedestalFinder);
	fdu->PedestalFinder->ColorRange = Range<CvScalar>(CV_RGB(5,6,7),CV_RGB(8,9,10));
	fdu->PedestalFinder->ScaleRange = Range<double>(2.1,3.2);
	fdu->PedestalFinder->SizeRange = Range<int>(11,12);
	fdu->Silk.ColorRange = Range<CvScalar>(CV_RGB(13,14,15),CV_RGB(16,17,18));
	fdu->Silk.PixelCount = 19;
	fdu->Silk.SearchRange = Range<int>(20,21);
	fdu->Lock.ColorRange = Range<CvScalar>(CV_RGB(22,23,24),CV_RGB(25,26,27));
	fdu->Lock.SearchRange = Range<int>(28,29);
	fdu->Lock.PixelCount = 30;
	fdu->Lock.XOffset = 31;
	fdu->Lock.SearchWidth = 4;
	shared_ptr<DetectionUnit> da(fdu);
	write_xml("./front_unit.xml",da->GetTree());

	read_xml("./front_unit.xml",pt_read);
	shared_ptr<DetectionUnit> read_da = DetectionUnitFactory::CreateUnitFromTree(pt_read);
	shared_ptr<FrontDetectionUnit> read_fdu = dynamic_pointer_cast<FrontDetectionUnit>(read_da);
	CPPUNIT_ASSERT(read_fdu);
	CPPUNIT_ASSERT_EQUAL(*fdu,*read_fdu);

	shared_ptr<BackDetectionUnit> bdu(new BackDetectionUnit);

	bdu->Name = "BackUnit";
	bdu->SubImageRect = cvRect(1,2,3,4);
	bdu->PedestalPosition = PEDESTAL_ON_BOTTOM;
	bdu->PedestalFinder = shared_ptr<PedestalFindAlgorithm>(new SimplePedestalFinder);
	bdu->PedestalFinder->ColorRange = Range<CvScalar>(CV_RGB(5,6,7),CV_RGB(8,9,10));
	bdu->PedestalFinder->ScaleRange = Range<double>(2.1,3.2);
	bdu->PedestalFinder->SizeRange = Range<int>(11,12);

	bdu->BlueBox.ColorRange = Range<CvScalar>(CV_RGB(13,14,15),CV_RGB(16,17,18));
	bdu->BlueBox.SearchRange = Range<int>(19,20);
	bdu->BlueBox.PixelCount = 21;

	bdu->Lock.ColorRange = Range<CvScalar>(CV_RGB(22,23,24),CV_RGB(25,26,27));
	bdu->Lock.SearchRange = Range<int>(28,29);
	bdu->Lock.PixelCount = 30;
	
	shared_ptr<DetectionUnit> da2(bdu);
	write_xml("./back_detection_unit.xml",da2->GetTree());	

	read_xml("./back_detection_unit.xml",pt_read);
	shared_ptr<DetectionUnit> da_read2 = DetectionUnitFactory::CreateUnitFromTree(pt_read);
	shared_ptr<BackDetectionUnit> bdu_read = dynamic_pointer_cast<BackDetectionUnit>(da_read2);
	CPPUNIT_ASSERT(bdu_read);
	CPPUNIT_ASSERT_EQUAL(*bdu,*bdu_read);


	shared_ptr<HardLockDetectionUnit> hld(new HardLockDetectionUnit);
	hld->Name = "HardLockUnit";
	hld->SubImageRect = cvRect(1,2,3,4);
	hld->PedestalPosition = PEDESTAL_ON_BOTTOM;
	hld->PedestalFinder = shared_ptr<PedestalFindAlgorithm>(new SimplePedestalFinder);
	hld->PedestalFinder->ColorRange = Range<CvScalar>(CV_RGB(5,6,7),CV_RGB(8,9,10));
	hld->PedestalFinder->ScaleRange = Range<double>(2.1,3.2);
	hld->PedestalFinder->SizeRange = Range<int>(11,12);

	hld->Silk.ColorRange = Range<CvScalar>(CV_RGB(13,14,15),CV_RGB(16,17,18));
	hld->Silk.PixelCount = 19;
	hld->Silk.SearchRange = Range<int>(20,21);
	hld->Silk.DetectFlag = ObjectDetectAlgorithm::DETECT_FLAG_APPEAR;

	hld->Lock.DetectFlag = ObjectDetectAlgorithm::DETECT_FLAG_APPEAR;
	hld->Lock.ColorRange = Range<CvScalar>(CV_RGB(22,23,24),CV_RGB(25,26,27));
	hld->Lock.SearchRange = Range<int>(28,29);
	hld->Lock.PixelCount = 30;
	hld->Lock.XOffset = 31;
	hld->Lock.SearchWidth = 4;
	shared_ptr<DetectionUnit> da3(hld);
	write_xml("./hard_detection_unit.xml",da3->GetTree());
	read_xml("./hard_detection_unit.xml",pt_read);
	shared_ptr<DetectionUnit> da_read3 = DetectionUnitFactory::CreateUnitFromTree(pt_read);
	shared_ptr<HardLockDetectionUnit> hld_read = dynamic_pointer_cast<HardLockDetectionUnit>(da_read3);
	CPPUNIT_ASSERT(hld_read);
	CPPUNIT_ASSERT_EQUAL(*hld,*hld_read);


	DetectionProgram dp("Test Detection Program");
	dp.push_back(da);
	dp.push_back(da3);
	dp.push_back(da2);
	write_xml("./detection_program.xml",dp.GetTree());

	read_xml("./detection_program.xml",pt_read);
	DetectionProgram dp_read;
	dp_read.ReadFromTree(pt_read);

	CPPUNIT_ASSERT_EQUAL(dp,dp_read);
	read_fdu = dynamic_pointer_cast<FrontDetectionUnit>(dp_read.front());
	CPPUNIT_ASSERT(read_fdu);
	CPPUNIT_ASSERT_EQUAL(*fdu,*read_fdu);
	bdu_read = dynamic_pointer_cast<BackDetectionUnit>(dp_read.back());
	CPPUNIT_ASSERT(bdu_read);
	CPPUNIT_ASSERT_EQUAL(*bdu,*bdu_read);


	DetectionLine dl("Test Detection Line");
	shared_ptr<DetectionProgram> program_ptr = shared_ptr<DetectionProgram>(new DetectionProgram);
	program_ptr->CopyOf(dp);
	dl.push_back(program_ptr);
	write_xml("./detection_line.xml",dl.GetTree());

	read_xml("./detection_line.xml",pt_read);
	DetectionLine dl_read;
	dl_read.ReadFromTree(pt_read);

	CPPUNIT_ASSERT_EQUAL(dl,dl_read);


}


void Test::Test_Clone()
{
	shared_ptr<FrontDetectionUnit> fdu(new FrontDetectionUnit);
	fdu->Name = "FrontUnit";
	fdu->SubImageRect = cvRect(1,2,3,4);
	fdu->PedestalPosition = PEDESTAL_ON_BOTTOM;
	fdu->PedestalFinder = shared_ptr<PedestalFindAlgorithm>(new SimplePedestalFinder);
	fdu->PedestalFinder->ColorRange = Range<CvScalar>(CV_RGB(5,6,7),CV_RGB(8,9,10));
	fdu->PedestalFinder->ScaleRange = Range<double>(2.1,3.2);
	fdu->PedestalFinder->SizeRange = Range<int>(11,12);
	fdu->Silk.ColorRange = Range<CvScalar>(CV_RGB(13,14,15),CV_RGB(16,17,18));
	fdu->Silk.PixelCount = 19;
	fdu->Silk.SearchRange = Range<int>(20,21);
	fdu->Lock.ColorRange = Range<CvScalar>(CV_RGB(22,23,24),CV_RGB(25,26,27));
	fdu->Lock.SearchRange = Range<int>(28,29);
	fdu->Lock.PixelCount = 30;
	fdu->Lock.XOffset = 31;

	shared_ptr<DetectionUnit> da(fdu);

	shared_ptr<DetectionUnit> da_clone = da->Clone();
	shared_ptr<FrontDetectionUnit> fdu_clone = dynamic_pointer_cast<FrontDetectionUnit>(da_clone);
	CPPUNIT_ASSERT(fdu_clone);
	CPPUNIT_ASSERT_EQUAL(*fdu,*fdu_clone);
	fdu_clone->SubImageRect = cvRect(4,3,2,1);
	CPPUNIT_ASSERT_ASSERTION_FAIL(CPPUNIT_ASSERT_EQUAL(*fdu,*fdu_clone));
}






void Test::Test_FrontDetectionUnit()
{
	shared_ptr<FrontDetectionUnit>  fdu(new FrontDetectionUnit);
	DetectionResult dr;

	fdu->PedestalPosition = PEDESTAL_ON_BOTTOM;

	fdu->PedestalFinder = shared_ptr<PedestalFindAlgorithm>(new SimplePedestalFinder);
	fdu->PedestalFinder->ColorRange = Range<CvScalar>(CV_RGB(190,190,190),CV_RGB(240,240,240));
	fdu->PedestalFinder->ScaleRange = Range<double>(3.2,3.8);
	fdu->PedestalFinder->SizeRange = Range<int>(370,450);

	fdu->Silk.ColorRange =  Range<CvScalar>(CV_RGB(190,190,190),CV_RGB(240,240,240));
	fdu->Silk.SearchRange = Range<int>(69,92);
	fdu->Silk.PixelCount = 250;

	fdu->Lock.ColorRange = Range<CvScalar>(CV_RGB(20,20,30),CV_RGB(75,75,75));
	fdu->Lock.PixelCount = 52;
	fdu->Lock.SearchRange = Range<int>(3,20);
	fdu->Lock.XOffset = 40;
	fdu->Lock.SearchWidth = 150;

	DetectionProgram dp;
	dp.push_back(fdu);
	IplImage_Ptr testImg;

	int result[23]={	1,1,1,1,1,
						1,0,0,0,1,
						1,0,1,1,1,
						1,0,0,0,0,
						0,0,0};
	for (int i=4;i<=23;i++)
	{
		boost::format fmt("E:\\project\\天宝电子\\排线检测\\myPic\\%d.jpg");
		fmt % i;
		testImg= cvLoadImage(fmt.str().c_str());
		CPPUNIT_ASSERT(testImg);
		cout << "\n检测图片文件" << i << ".jpg";
		dp.Detect(testImg,dr);
		cout << "\t------"<<dr.ErrorString;
		
		if(result[i-1])
			CPPUNIT_ASSERT_EQUAL(true,dr.IsPass);
		else
			CPPUNIT_ASSERT_EQUAL(false,dr.IsPass);
	}
}



void Test::Test_FrontDetectioinUnit2()
{
	shared_ptr<FrontDetectionUnit>  sa(new FrontDetectionUnit);
	DetectionResult dr;


	sa->PedestalPosition = PEDESTAL_ON_BOTTOM;

	sa->PedestalFinder = shared_ptr<PedestalFindAlgorithm>(new SimplePedestalFinder);
	sa->PedestalFinder->ColorRange = Range<CvScalar>(CV_RGB(190,190,190),CV_RGB(240,240,240));
	sa->PedestalFinder->ScaleRange = Range<double>(1.8,2.5);
	sa->PedestalFinder->SizeRange = Range<int>(280,380);

	sa->Silk.ColorRange =  Range<CvScalar>(CV_RGB(40,40,40),CV_RGB(110,130,150));
	sa->Silk.SearchRange = Range<int>(65,81);
	sa->Silk.PixelCount = 150;

	sa->Lock.ColorRange = Range<CvScalar>(CV_RGB(60,70,70),CV_RGB(130,120,110));
	sa->Lock.PixelCount = 40;
	sa->Lock.SearchRange = Range<int>(-5,10);
	sa->Lock.XOffset = 60;
	sa->Lock.SearchWidth = 120;

	IplImage_Ptr testImg;

	DetectionProgram dp;
	dp.push_back(sa);


	int result[]={		1,1,0,0,0,
						0,0,1,1,1,
						1,1,0,1,0,
						0,0,0,0,0,
						0,0,0,0,0,
						0};
	for (int i=1;i<=26;i++)
	{
		boost::format fmt("E:\\project\\天宝电子\\排线检测\\left2Pic\\%d.jpg");
		fmt % i;
		testImg= cvLoadImage(fmt.str().c_str());
		CPPUNIT_ASSERT(testImg);
		cout << "\n检测图片文件" << i << ".jpg";
		dp.Detect(testImg,dr);
		cout << "\t------"<<dr.ErrorString;

		if(result[i-1])
			CPPUNIT_ASSERT_EQUAL(true,dr.IsPass);
		else
			CPPUNIT_ASSERT_EQUAL(false,dr.IsPass);
	}
}

void Test::Test_FrontDetectionUnitSilkOnBottom()
{
	shared_ptr<FrontDetectionUnit>  sa(new FrontDetectionUnit);
	DetectionResult dr;

	sa->PedestalPosition = PEDESTAL_ON_TOP;
	sa->PedestalFinder = shared_ptr<PedestalFindAlgorithm>(new SimplePedestalFinder);
	sa->PedestalFinder->ColorRange = Range<CvScalar>(CV_HSV(0,2,80),CV_HSV(100,10,90));
	sa->PedestalFinder->ScaleRange = Range<double>(2.0,2.8);
	sa->PedestalFinder->SizeRange = Range<int>(310,410);

	sa->Silk.ColorRange =  Range<CvScalar>(CV_RGB(40,40,40),CV_RGB(110,130,150));
	sa->Silk.SearchRange = Range<int>(65,81);
	sa->Silk.PixelCount = 150;

	sa->Lock.ColorRange = Range<CvScalar>(CV_RGB(60,70,70),CV_RGB(130,120,110));
	sa->Lock.PixelCount = 40;
	sa->Lock.SearchRange = Range<int>(-8,10);
	sa->Lock.XOffset = 60;
	sa->Lock.SearchWidth = 140;

	DetectionProgram dp;
	dp.push_back(sa);


	IplImage_Ptr testImg;

	int result[]={		1,1,0,1,1,
						0,0,0,1,1,
						1,1,1,1,0,
						0,0,0,0,0,
						0,0};
	for (int i=1;i<=22;i++)
	{
		boost::format fmt("E:\\project\\天宝电子\\排线检测\\left1Pic\\%d.jpg");
		fmt % i;
		testImg= cvLoadImage(fmt.str().c_str());
		CPPUNIT_ASSERT(testImg);
		cout << "\n检测图片文件" << i << ".jpg";
		dp.Detect(testImg,dr);
		cout << "\t------"<<dr.ErrorString;
		/*if(!dr.IsPass)
		{
			cvNamedWindow("hello");
			cvShowImage("hello",dr.ResultImage);
			cvWaitKey(0);
			cvDestroyWindow("hello");
		}*/
		if(result[i-1])
			CPPUNIT_ASSERT_EQUAL(true,dr.IsPass);
		else
			CPPUNIT_ASSERT_EQUAL(false,dr.IsPass);
	}
}



void Test::Test_InclinedPicture()
{
	shared_ptr<FrontDetectionUnit>  sa(new FrontDetectionUnit);
	DetectionResult dr;

	sa->PedestalPosition = PEDESTAL_ON_TOP;
	sa->PedestalFinder = shared_ptr<PedestalFindAlgorithm>(new InclinedPedestalFinder);
	sa->PedestalFinder->ColorRange = Range<CvScalar>(CV_HSV(0,2,80),CV_HSV(100,10,90));
	sa->PedestalFinder->ScaleRange = Range<double>(2.0,2.8);
	sa->PedestalFinder->SizeRange = Range<int>(310,410);

	sa->Silk.ColorRange =  Range<CvScalar>(CV_RGB(40,40,40),CV_RGB(110,130,150));
	sa->Silk.SearchRange = Range<int>(65,81);
	sa->Silk.PixelCount = 150;

	sa->Lock.ColorRange = Range<CvScalar>(CV_RGB(60,70,70),CV_RGB(130,120,110));
	sa->Lock.PixelCount = 40;
	sa->Lock.SearchRange = Range<int>(-8,10);
	sa->Lock.XOffset = 60;
	sa->Lock.SearchWidth = 140;

	DetectionProgram dp;
	dp.push_back(sa);

	IplImage_Ptr testImg;

	testImg= cvLoadImage("E:\\project\\天宝电子\\排线检测\\left1Pic\\8.jpg");
	CPPUNIT_ASSERT(testImg);
	dp.Detect(testImg,dr);
	cout << dr.ErrorString;
	cvNamedWindow("hello");
	cvShowImage("hello",dr.ResultImage);
	cvWaitKey();
	CPPUNIT_ASSERT_EQUAL(true,dr.IsPass);
}


void Test::Test_HSV()
{
	CPPUNIT_ASSERT_EQUAL(true,IsHSV(CV_HSV(1,1,1)));
	CPPUNIT_ASSERT_EQUAL(false,IsHSV(CV_RGB(1,1,1)));


	//CPPUNIT_ASSERT_EQUAL(CV_HSV(209,100,60),CvtRGB2HSV(CV_RGB(0,78,152)));
	/*IplImage_Ptr img = cvLoadImage("F:\\project\\天宝电子\\排线检测\\left1Pic\\1.jpg");
	
	IplImage_Ptr grayImage = cvCreateImage(cvGetSize(img),img->depth,1);
	
	ThreshColorImage(img,grayImage,Range<CvScalar>(CV_HSV(0,2,80),CV_HSV(100,10,90)));*/

}

void Test::Test_DetectProgram()
{
	DetectionResult dr;
	shared_ptr<FrontDetectionUnit> CenterSilkAlgorithm (new FrontDetectionUnit);

	CenterSilkAlgorithm->SubImageRect = cvRect(2319,1491,677,654);

	CenterSilkAlgorithm->PedestalPosition = PEDESTAL_ON_BOTTOM;
	
	CenterSilkAlgorithm->PedestalFinder = shared_ptr<PedestalFindAlgorithm>(new SimplePedestalFinder);

	CenterSilkAlgorithm->PedestalFinder->ColorRange = Range<CvScalar>(CV_RGB(190,190,190),CV_RGB(240,240,240));
	CenterSilkAlgorithm->PedestalFinder->ScaleRange = Range<double>(3.2,3.8);
	CenterSilkAlgorithm->PedestalFinder->SizeRange = Range<int>(370,450);

	CenterSilkAlgorithm->Silk.ColorRange =  Range<CvScalar>(CV_RGB(190,190,190),CV_RGB(240,240,240));
	CenterSilkAlgorithm->Silk.SearchRange = Range<int>(69,92);
	CenterSilkAlgorithm->Silk.PixelCount = 250;

	CenterSilkAlgorithm->Lock.ColorRange = Range<CvScalar>(CV_RGB(20,20,30),CV_RGB(75,75,75));
	CenterSilkAlgorithm->Lock.PixelCount = 52;
	CenterSilkAlgorithm->Lock.SearchRange = Range<int>(3,20);
	CenterSilkAlgorithm->Lock.XOffset = 40;
	CenterSilkAlgorithm->Lock.SearchWidth = 150;
	
	shared_ptr<FrontDetectionUnit> Left2Algorithm(new FrontDetectionUnit);

	Left2Algorithm->SubImageRect = cvRect(1306,910,640,513);

	Left2Algorithm->PedestalPosition = PEDESTAL_ON_BOTTOM;

	Left2Algorithm->PedestalFinder = shared_ptr<PedestalFindAlgorithm>(new SimplePedestalFinder);
	Left2Algorithm->PedestalFinder->ColorRange = Range<CvScalar>(CV_RGB(190,190,190),CV_RGB(240,240,240));
	Left2Algorithm->PedestalFinder->ScaleRange = Range<double>(1.8,2.5);
	Left2Algorithm->PedestalFinder->SizeRange = Range<int>(280,380);

	Left2Algorithm->Silk.ColorRange =  Range<CvScalar>(CV_RGB(40,40,40),CV_RGB(110,130,150));
	Left2Algorithm->Silk.SearchRange = Range<int>(65,81);
	Left2Algorithm->Silk.PixelCount = 150;

	Left2Algorithm->Lock.ColorRange = Range<CvScalar>(CV_RGB(60,70,70),CV_RGB(130,120,110));
	Left2Algorithm->Lock.PixelCount = 40;
	Left2Algorithm->Lock.SearchRange = Range<int>(-5,10);
	Left2Algorithm->Lock.XOffset = 60;
	Left2Algorithm->Lock.SearchWidth = 130;

	shared_ptr<FrontDetectionUnit> Left1Algorithm( new FrontDetectionUnit);

	Left1Algorithm->SubImageRect = cvRect(1306,428,659,470);

	Left1Algorithm->PedestalPosition = PEDESTAL_ON_TOP;

	Left1Algorithm->PedestalFinder = shared_ptr<PedestalFindAlgorithm>(new SimplePedestalFinder);
	Left1Algorithm->PedestalFinder->ColorRange = Range<CvScalar>(CV_HSV(0,2,80),CV_HSV(100,10,90));
	Left1Algorithm->PedestalFinder->ScaleRange = Range<double>(2.0,2.8);
	Left1Algorithm->PedestalFinder->SizeRange = Range<int>(310,410);

	Left1Algorithm->Silk.ColorRange =  Range<CvScalar>(CV_RGB(40,40,40),CV_RGB(110,130,150));
	Left1Algorithm->Silk.SearchRange = Range<int>(65,81);
	Left1Algorithm->Silk.PixelCount = 150;

	Left1Algorithm->Lock.ColorRange = Range<CvScalar>(CV_RGB(60,70,70),CV_RGB(130,120,110));
	Left1Algorithm->Lock.PixelCount = 40;
	Left1Algorithm->Lock.SearchRange = Range<int>(-8,10);
	Left1Algorithm->Lock.XOffset = 60;
	Left1Algorithm->Lock.SearchWidth = 140;

	

	DetectionProgram dp;
	dp.push_back(CenterSilkAlgorithm);
	dp.push_back(Left2Algorithm);
	dp.push_back(Left1Algorithm);


	IplImage_Ptr testImg = cvLoadImage("E:\\project\\天宝电子\\排线检测\\testWholePic\\1.jpg");

	dp.Detect(testImg,dr);
	CPPUNIT_ASSERT_EQUAL(true,dr.IsPass);
	/*cvNamedWindow("hello");
	cvShowImage("hello",dr.ResultImage);
	cvWaitKey();*/
}

void Test::Test_DetectProgramRealPic()
{
	DetectionResult dr;
	shared_ptr<FrontDetectionUnit> CenterSilkAlgorithm (new FrontDetectionUnit);

	CenterSilkAlgorithm->SubImageRect = cvRect(484,488,143,140);
	CenterSilkAlgorithm->PedestalPosition = PEDESTAL_ON_BOTTOM;

	CenterSilkAlgorithm->PedestalFinder = shared_ptr<PedestalFindAlgorithm>(new SimplePedestalFinder);
	CenterSilkAlgorithm->PedestalFinder->ColorRange = Range<CvScalar>(CV_RGB(120,120,110),CV_RGB(140,140,130));
	CenterSilkAlgorithm->PedestalFinder->ScaleRange = Range<double>(2.1,4.6);
	CenterSilkAlgorithm->PedestalFinder->SizeRange = Range<int>(80,110);

	CenterSilkAlgorithm->Silk.ColorRange =  Range<CvScalar>(CV_RGB(130,130,130),CV_RGB(160,160,160));
	CenterSilkAlgorithm->Silk.SearchRange = Range<int>(20,23);
	CenterSilkAlgorithm->Silk.PixelCount = 50;

	CenterSilkAlgorithm->Lock.ColorRange = Range<CvScalar>(CV_RGB(20,20,30),CV_RGB(35,40,40));
	CenterSilkAlgorithm->Lock.PixelCount = 16;
	CenterSilkAlgorithm->Lock.SearchRange = Range<int>(1,6);
	CenterSilkAlgorithm->Lock.XOffset = 11;
	CenterSilkAlgorithm->Lock.SearchWidth = 40;

	shared_ptr<FrontDetectionUnit> Left2Algorithm (new FrontDetectionUnit);

	Left2Algorithm->SubImageRect = cvRect(249,333,135,106);
	Left2Algorithm->PedestalPosition = PEDESTAL_ON_BOTTOM;

	Left2Algorithm->PedestalFinder = shared_ptr<PedestalFindAlgorithm>(new SimplePedestalFinder);
	Left2Algorithm->PedestalFinder->ColorRange = Range<CvScalar>(CV_RGB(130,130,120),CV_RGB(150,150,140));
	Left2Algorithm->PedestalFinder->ScaleRange = Range<double>(1.8,2.3);
	Left2Algorithm->PedestalFinder->SizeRange = Range<int>(65,80);

	Left2Algorithm->Silk.ColorRange =  Range<CvScalar>(CV_RGB(30,30,40),CV_RGB(60,60,70));
	Left2Algorithm->Silk.SearchRange = Range<int>(14,18);
	Left2Algorithm->Silk.PixelCount = 45;

	Left2Algorithm->Lock.ColorRange = Range<CvScalar>(CV_RGB(40,40,40),CV_RGB(60,55,60));
	Left2Algorithm->Lock.PixelCount = 12;
	Left2Algorithm->Lock.SearchRange = Range<int>(-2,5);
	Left2Algorithm->Lock.XOffset = 16;
	Left2Algorithm->Lock.SearchWidth = 28;

	shared_ptr<FrontDetectionUnit> Left1Algorithm (new FrontDetectionUnit);

	Left1Algorithm->SubImageRect = cvRect(249,233,132,102);
	Left1Algorithm->PedestalPosition = PEDESTAL_ON_TOP;

	Left1Algorithm->PedestalFinder = shared_ptr<PedestalFindAlgorithm>(new SimplePedestalFinder);
	Left1Algorithm->PedestalFinder->ColorRange = Range<CvScalar>(CV_RGB(120,130,110),CV_RGB(160,160,140));
	Left1Algorithm->PedestalFinder->ScaleRange = Range<double>(1.,3.8);
	Left1Algorithm->PedestalFinder->SizeRange =  Range<int>(70,115);

	Left1Algorithm->Silk.ColorRange =  Range<CvScalar>(CV_RGB(30,30,40),CV_RGB(60,60,70));
	Left1Algorithm->Silk.SearchRange = Range<int>(14,18);
	Left1Algorithm->Silk.PixelCount = 45;

	Left1Algorithm->Lock.ColorRange = Range<CvScalar>(CV_HSV(0,0,0),CV_HSV(80,30,30));
	Left1Algorithm->Lock.PixelCount = 10;
	Left1Algorithm->Lock.SearchRange = Range<int>(-2,8);
	Left1Algorithm->Lock.XOffset = 12;
	Left1Algorithm->Lock.SearchWidth = 40;

	

	DetectionProgram dp;
	dp.push_back(CenterSilkAlgorithm);
	dp.push_back(Left2Algorithm);
	dp.push_back(Left1Algorithm);


	IplImage_Ptr testImg = cvLoadImage("E:\\project\\天宝电子\\排线检测\\testWholePic\\2.jpg");

	dp.Detect(testImg,dr);
	CPPUNIT_ASSERT_EQUAL(true,dr.IsPass);
	cout << endl << dr.ErrorString << endl;
	/*if(!dr.IsPass)
	{
		cvNamedWindow("hello");
		cvShowImage("hello",dr.ResultImage);
		cvWaitKey();
		cvDestroyWindow("hello");
	}
	*/
}

void Test::Test_BackDetectionUnit()
{
	DetectionResult dr;
	shared_ptr<BackDetectionUnit> ba(new BackDetectionUnit);

	ba->SubImageRect = cvRect(0,0,600,400);

	ba->PedestalPosition = PEDESTAL_ON_BOTTOM;
	ba->PedestalFinder = shared_ptr<PedestalFindAlgorithm>(new SimplePedestalFinder);
	ba->PedestalFinder->ColorRange = Range<CvScalar>(CV_RGB(80,90,70),CV_RGB(130,140,120));
	ba->PedestalFinder->ScaleRange = Range<double>(3.5,20.);
	ba->PedestalFinder->SizeRange = Range<int>(350,500);

	ba->BlueBox.ColorRange =  Range<CvScalar>(CV_RGB(0,40,70),CV_RGB(16,80,130));
	ba->BlueBox.SearchRange = Range<int>(110,120);
	ba->BlueBox.PixelCount = 170;

	ba->Lock.ColorRange = Range<CvScalar>(CV_RGB(0,0,0),CV_RGB(20,20,20));
	ba->Lock.PixelCount = 250;
	ba->Lock.SearchRange = Range<int>(50,60);


	DetectionProgram dp;
	dp.push_back(ba);


	IplImage_Ptr testImg = cvLoadImage("E:\\project\\天宝电子\\排线检测\\testBackPic\\1.jpg");
	dp.Detect(testImg,dr);
	cout << endl << dr.ErrorString << endl;
	CPPUNIT_ASSERT_EQUAL(false,dr.IsPass);
	/*if(!dr.IsPass)
	{
		cvNamedWindow("hello");
		cvShowImage("hello",dr.ResultImage);
		cvWaitKey();
		cvDestroyWindow("hello");
	}*/


}

void Test::Test_HardFrontDetectionUnit()
{
	shared_ptr<HardLockDetectionUnit> hld (new HardLockDetectionUnit);
	DetectionResult dr;

	hld->SubImageRect = cvRect(400,250,250,200);
	hld->PedestalPosition = PEDESTAL_ON_BOTTOM;
	hld->PedestalFinder = shared_ptr<PedestalFindAlgorithm>(new SimplePedestalFinder);
	hld->PedestalFinder->ColorRange = Range<CvScalar>(CV_HSV(90,26,42),CV_HSV(110,33,52));
	hld->PedestalFinder->ScaleRange = Range<double>(3.,10.);
	hld->PedestalFinder->SizeRange = Range<int>(100,250);

	hld->Lock.ColorRange = Range<CvScalar>(CV_RGB(20,30,20),CV_RGB(40,50,45));
	hld->Lock.SearchRange = Range<int>(-4,2);
	hld->Lock.SearchWidth = 30;
	hld->Lock.XOffset = 10;
	hld->Lock.PixelCount = 16;

	DetectionProgram dp;
	dp.push_back(hld);
	IplImage_Ptr testImg;

	int result[]={1,0,0};
	for (int i=1;i<=3;i++)
	{
		/*boost::format fmt("E:\\project\\天宝电子\\排线检测\\HardLock\\%d.jpg");
		fmt % i;
		testImg= cvLoadImage(fmt.str().c_str());
		CPPUNIT_ASSERT(testImg);
		cout << "\n检测图片文件" << i << ".jpg";
		dp.Detect(testImg,dr);
		cout << "\t------"<<dr.ErrorString;
		if(!dr.IsPass)
		{
			cvNamedWindow("hello");
			cvShowImage("hello",dr.ResultImage);
			cvWaitKey(0);
			cvDestroyWindow("hello");
		}
		if(result[i-1])
			CPPUNIT_ASSERT_EQUAL(true,dr.IsPass);
		else
			CPPUNIT_ASSERT_EQUAL(false,dr.IsPass);*//**/
	}
}

void Test::Test_PedestalFind()
{
	/*shared_ptr<ConstHeightPedestalFinder> pfa(new ConstHeightPedestalFinder);
	
	pfa->ExpectHeight = 76;
	pfa->ReferenceDirection = DIRECTION_FROM_TOP;

	pfa->ColorRange = Range<CvScalar>(CV_HSV(70,15,20),CV_HSV(100,28,26));
	pfa->SizeRange = Range<int>(60,75);
	pfa->ScaleRange = Range<double>(0.8,1.1);
	pfa->XLeastPointNumber = 40;
	pfa->YLeastPointNumber = 40;

	IplImage_Ptr testImg;
	testImg = cvLoadImage("E:\\project\\天宝电子\\排线检测\\blue\\no.jpg");

	CvRect FindPedestalRect = pfa->Find(testImg);
	CPPUNIT_ASSERT_EQUAL(pfa->ExpectHeight,FindPedestalRect.height);*/

	/*FillRect(testImg,FindPedestalRect,CV_RGB(100,100,0));
	
	cvNamedWindow("test");
	cvShowImage("test",testImg);
	cvWaitKey(0);
	cvDestroyWindow("hello");
	*/
}

void Test::Test_Silk_LeftAndRight()
{
	shared_ptr<FrontDetectionUnit>  fdu(new FrontDetectionUnit);
	DetectionResult dr;

	fdu->PedestalPosition = PEDESTAL_ON_BOTTOM;

	fdu->PedestalFinder = shared_ptr<PedestalFindAlgorithm>(new SimplePedestalFinder);
	fdu->PedestalFinder->ColorRange = Range<CvScalar>(CV_RGB(190,190,190),CV_RGB(240,240,240));
	fdu->PedestalFinder->ScaleRange = Range<double>(3.2,3.8);
	fdu->PedestalFinder->SizeRange = Range<int>(370,450);

	fdu->Silk.ColorRange =  Range<CvScalar>(CV_RGB(190,190,190),CV_RGB(240,240,240));
	fdu->Silk.SearchRange = Range<int>(69,92);
	fdu->Silk.PixelCount = 16;
	fdu->Silk.XOffset = 65;
	fdu->Silk.SearchWidth = 30;
	fdu->Silk.MaxGapAround = -1;

	fdu->Lock.ColorRange = Range<CvScalar>(CV_RGB(20,20,30),CV_RGB(75,75,75));
	fdu->Lock.PixelCount = 52;
	fdu->Lock.SearchRange = Range<int>(3,20);
	fdu->Lock.XOffset = 40;
	fdu->Lock.SearchWidth = 150;

	DetectionProgram dp;
	dp.push_back(fdu);
	IplImage_Ptr testImg;

	testImg= cvLoadImage("E:\\project\\天宝电子\\排线检测\\myPic\\6.jpg");
	CPPUNIT_ASSERT(testImg);
	cout << "\n检测图片文件" << 6 << ".jpg";
	dp.Detect(testImg,dr);
	cout << "\t------"<<dr.ErrorString;
	if(!dr.IsPass)
	{
		cvNamedWindow("hello");
		cvShowImage("hello",dr.ResultImage);
		cvWaitKey(0);
		cvDestroyWindow("hello");
	}
}

void Test::Test_md5()
{
	//cout << endl << MD5("cumthugo").toString() << endl;
	MD5 md5;
	md5.update("1234");
	md5.update(md5.toString());
	cout << endl << md5.toString() << endl;
}
