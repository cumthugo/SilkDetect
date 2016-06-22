/********************************************************************
	Created:	2011/08/12
	Filename: 	test.h
	Author:		Hugo
	Purpose:	test header
*********************************************************************/

#pragma once

#include <cppunit/extensions/HelperMacros.h>

class TestUnit;

class Test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(Test);
	CPPUNIT_TEST(Test_UnitSerialization);
	CPPUNIT_TEST(Test_Clone);
	CPPUNIT_TEST(Test_HSV);
	CPPUNIT_TEST(Test_RestrictRect);
	CPPUNIT_TEST(Test_HardFrontDetectionUnit);
	
	CPPUNIT_TEST(Test_FrontDetectionUnitSilkOnBottom);
	CPPUNIT_TEST(Test_FrontDetectionUnit);
	CPPUNIT_TEST(Test_FrontDetectioinUnit2);
	CPPUNIT_TEST(Test_DetectProgram);
	CPPUNIT_TEST(Test_DetectProgramRealPic);
	CPPUNIT_TEST(Test_BackDetectionUnit);
	
	CPPUNIT_TEST(Test_PedestalFind);
	CPPUNIT_TEST(Test_Silk_LeftAndRight);
	CPPUNIT_TEST(Test_md5);
	CPPUNIT_TEST(Test_InclinedPicture);/**/

	CPPUNIT_TEST_SUITE_END();
public:
	//void setUp();
	//void tearDown();


	void Test_RestrictRect();

	void Test_HSV();


	void Test_UnitSerialization();


	void Test_Clone();

	void Test_FrontDetectionUnitSilkOnBottom();

	void Test_FrontDetectionUnit();

	void Test_FrontDetectioinUnit2();

	void Test_DetectProgram();

	void Test_DetectProgramRealPic();

	void Test_BackDetectionUnit();

	void Test_HardFrontDetectionUnit();

	void Test_PedestalFind();

	void Test_Silk_LeftAndRight();

	void Test_md5();

	void Test_InclinedPicture();

private:
};

