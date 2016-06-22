/********************************************************************
	Created:	2014/08/12
	Filename: 	testLogic.h
	Author:		Hugo
	Purpose:	test Logic header
*********************************************************************/


#pragma once

#include <cppunit/extensions/HelperMacros.h>

class TestLogic : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestLogic);

	CPPUNIT_TEST(Test_SimplePass);
	CPPUNIT_TEST(Test_NotSilkErrorNormal);
	CPPUNIT_TEST(Test_SimpleSilkError);
	CPPUNIT_TEST(Test_SimpleSilkErrorReset);
	CPPUNIT_TEST(Test_SilkErrorAndOtherError);
	CPPUNIT_TEST(Test_DoubleSilkError);
	CPPUNIT_TEST(Test_DoubleSilkError2);
	CPPUNIT_TEST(Test_DoubleError);
	CPPUNIT_TEST(Test_ListIterator);
	CPPUNIT_TEST(Test_BugError);
	CPPUNIT_TEST_SUITE_END();

public:
	void Test_SimplePass();
	void Test_NotSilkErrorNormal();
	void Test_SimpleSilkError();
	void Test_SimpleSilkErrorReset();
	void Test_SilkErrorAndOtherError();
	void Test_DoubleSilkError();
	void Test_DoubleSilkError2();
	void Test_DoubleError();
	void Test_BugError();

	void Test_ListIterator();
	
private:
	int detect_reuslt[3];
};