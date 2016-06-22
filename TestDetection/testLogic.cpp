#include <cppunit/config/SourcePrefix.h>

#include "testLogic.h"


#include "../DetectionLib/MyLib.hpp"

#include "../DetectionLib/FrontDetectionUnit.hpp"
#include "../DetectionLib/DetectionProgram.hpp"
#include "../DetectionLib/DetectionLine.hpp"
#include "../DetectionLib/BackDetectionUnit.hpp"
#include "../DetectionLib/HardLockDetectionUnit.hpp"
#include "../DetectionLib/DetectionUnitFactory.hpp"
#include "../DetectionLib/NoLockDetectionUnit.hpp"

#include "../DetectionLib/PedestalFindAlgorithm.hpp"


#include <list>
#include <iostream>


CPPUNIT_TEST_SUITE_REGISTRATION(TestLogic);

class DetectLogic
{
public:
	DetectLogic():lockNumber(0){}
	int Detect(int results[])
	{		
		if(lockNumber == 0)
		{
			for(int i=0;i<3;i++)
			{
				if(results[i] != RESULT_PASS)
				{
					if(results[i] == RESULT_FAIL_SILK) lockNumber = i;//_lock[i] = true;
					return results[i];
				}				
			}	
			return RESULT_PASS;
		}
		else
		{
			if(results[lockNumber] == RESULT_FAIL_CABLE)
			{
				lockNumber = 0;
				return RESULT_FAIL_CABLE;
			}
			else{
				return RESULT_FAIL_SILK;
			}
		}		
	}
private:
	int lockNumber;
};



void TestLogic::Test_SimplePass()
{
	detect_reuslt[0] = detect_reuslt[1] = detect_reuslt[2] = RESULT_PASS;

	DetectLogic dl;

	CPPUNIT_ASSERT_EQUAL(RESULT_PASS,dl.Detect(detect_reuslt));


}

void TestLogic::Test_NotSilkErrorNormal()
{
	DetectLogic dl;
	detect_reuslt[0] = detect_reuslt[1] = detect_reuslt[2] = RESULT_PASS;

	for(int errorcode=-1;errorcode>-8;errorcode--)
	{
		if(errorcode != RESULT_FAIL_SILK)
		{
			detect_reuslt[0] = errorcode;
			CPPUNIT_ASSERT_EQUAL(errorcode,dl.Detect(detect_reuslt));
			detect_reuslt[0] = detect_reuslt[1] = detect_reuslt[2] = RESULT_PASS;
			CPPUNIT_ASSERT_EQUAL(RESULT_PASS,dl.Detect(detect_reuslt));
		}		
	}

}

void TestLogic::Test_SimpleSilkError()
{
	DetectLogic dl;
	detect_reuslt[0] = detect_reuslt[2] = RESULT_PASS;
	detect_reuslt[1] = RESULT_FAIL_SILK;
	CPPUNIT_ASSERT_EQUAL(RESULT_FAIL_SILK,dl.Detect(detect_reuslt));

	detect_reuslt[0] = detect_reuslt[1] = detect_reuslt[2] = RESULT_PASS;
	CPPUNIT_ASSERT_EQUAL(RESULT_FAIL_SILK,dl.Detect(detect_reuslt));
}

void TestLogic::Test_SimpleSilkErrorReset()
{
	DetectLogic dl;
	detect_reuslt[0] = detect_reuslt[2] = RESULT_PASS;
	detect_reuslt[1] = RESULT_FAIL_SILK;
	CPPUNIT_ASSERT_EQUAL(RESULT_FAIL_SILK,dl.Detect(detect_reuslt));

	detect_reuslt[1] = RESULT_FAIL_CABLE;
	CPPUNIT_ASSERT_EQUAL(RESULT_FAIL_CABLE,dl.Detect(detect_reuslt));

	detect_reuslt[0] = detect_reuslt[1] = detect_reuslt[2] = RESULT_PASS;
	CPPUNIT_ASSERT_EQUAL(RESULT_PASS,dl.Detect(detect_reuslt));
}

void TestLogic::Test_SilkErrorAndOtherError()
{
	DetectLogic dl;
	detect_reuslt[0] = detect_reuslt[2] = RESULT_PASS;
	detect_reuslt[1] = RESULT_FAIL_SILK;
	CPPUNIT_ASSERT_EQUAL(RESULT_FAIL_SILK,dl.Detect(detect_reuslt));

	detect_reuslt[0] = RESULT_FAIL_LOCK;
	detect_reuslt[1] = RESULT_FAIL_CABLE;

	CPPUNIT_ASSERT_EQUAL(RESULT_FAIL_CABLE,dl.Detect(detect_reuslt));

	CPPUNIT_ASSERT_EQUAL(RESULT_FAIL_LOCK,dl.Detect(detect_reuslt));

	detect_reuslt[0] = detect_reuslt[1] = detect_reuslt[2] = RESULT_PASS;
	CPPUNIT_ASSERT_EQUAL(RESULT_PASS,dl.Detect(detect_reuslt));

}

void TestLogic::Test_DoubleSilkError()
{
	DetectLogic dl;
	detect_reuslt[0] =  RESULT_PASS;
	detect_reuslt[1] = detect_reuslt[2] = RESULT_FAIL_SILK;
	CPPUNIT_ASSERT_EQUAL(RESULT_FAIL_SILK,dl.Detect(detect_reuslt));

	detect_reuslt[1] = RESULT_FAIL_CABLE;		
	CPPUNIT_ASSERT_EQUAL(RESULT_FAIL_CABLE,dl.Detect(detect_reuslt));

	detect_reuslt[1] = RESULT_PASS;
	CPPUNIT_ASSERT_EQUAL(RESULT_FAIL_SILK,dl.Detect(detect_reuslt));

	detect_reuslt[2] = RESULT_FAIL_CABLE;		
	CPPUNIT_ASSERT_EQUAL(RESULT_FAIL_CABLE,dl.Detect(detect_reuslt));

	detect_reuslt[0] = detect_reuslt[1] = detect_reuslt[2] = RESULT_PASS;
	CPPUNIT_ASSERT_EQUAL(RESULT_PASS,dl.Detect(detect_reuslt));
}

void TestLogic::Test_DoubleSilkError2()
{
	DetectLogic dl;
	detect_reuslt[0] =  RESULT_PASS;
	detect_reuslt[1] = detect_reuslt[2] = RESULT_FAIL_SILK;
	CPPUNIT_ASSERT_EQUAL(RESULT_FAIL_SILK,dl.Detect(detect_reuslt));

	detect_reuslt[1] = detect_reuslt[2] = RESULT_FAIL_CABLE;

	CPPUNIT_ASSERT_EQUAL(RESULT_FAIL_CABLE,dl.Detect(detect_reuslt));

	detect_reuslt[0] = detect_reuslt[1] = detect_reuslt[2] = RESULT_PASS;
	CPPUNIT_ASSERT_EQUAL(RESULT_PASS,dl.Detect(detect_reuslt));
}

void TestLogic::Test_DoubleError()
{
	DetectLogic dl;
	detect_reuslt[0] =  RESULT_FAIL_LOCK;
	detect_reuslt[1] =  RESULT_FAIL_SILK;
	detect_reuslt[2] =  RESULT_PASS;

	CPPUNIT_ASSERT_EQUAL(RESULT_FAIL_LOCK,dl.Detect(detect_reuslt));

	CPPUNIT_ASSERT_EQUAL(RESULT_FAIL_LOCK,dl.Detect(detect_reuslt));
	CPPUNIT_ASSERT_EQUAL(RESULT_FAIL_LOCK,dl.Detect(detect_reuslt));
}

void TestLogic::Test_BugError()
{
	DetectLogic dl;
	detect_reuslt[0] =  RESULT_PASS;
	detect_reuslt[1] =  RESULT_FAIL_SILK;
	detect_reuslt[2] =  RESULT_PASS;

	CPPUNIT_ASSERT_EQUAL(RESULT_FAIL_SILK,dl.Detect(detect_reuslt));

	CPPUNIT_ASSERT_EQUAL(RESULT_FAIL_SILK,dl.Detect(detect_reuslt));
	detect_reuslt[1] =  RESULT_FAIL_CABLE;
	CPPUNIT_ASSERT_EQUAL(RESULT_FAIL_CABLE,dl.Detect(detect_reuslt));
	CPPUNIT_ASSERT_EQUAL(RESULT_FAIL_CABLE,dl.Detect(detect_reuslt));
	CPPUNIT_ASSERT_EQUAL(RESULT_FAIL_CABLE,dl.Detect(detect_reuslt));
}


template <typename T>
bool IsIteartorInList(std::list<T>& l, typename std::list<T>::iterator it)
{
	for (std::list<T>::iterator iter = l.begin(); iter!=l.end(); ++iter)
	{
		if(it == iter) return true;
	}
	return false;
}

void TestLogic::Test_ListIterator()
{
	using namespace std;
	list<int> arr;
	list<int>::iterator it_end = arr.end();
	
	for(int i=0;i<10;i++)
		arr.push_back(i);
	CPPUNIT_ASSERT(it_end == arr.end());
	list<int>::iterator it_begin = arr.begin();
	//remove one item
	arr.remove(5);
	CPPUNIT_ASSERT(it_begin == arr.begin());
	CPPUNIT_ASSERT(IsIteartorInList(arr,it_begin));
	arr.remove(1);
	CPPUNIT_ASSERT(it_begin == arr.begin());
	CPPUNIT_ASSERT(IsIteartorInList(arr,it_begin));
	arr.remove(0);
	CPPUNIT_ASSERT(it_begin != arr.begin());
	CPPUNIT_ASSERT(false == IsIteartorInList(arr,it_begin));

	arr.clear();	
	CPPUNIT_ASSERT(it_end == arr.end());
	for(int i=0;i<10;i++)
		arr.push_back(i);
	CPPUNIT_ASSERT(it_end == arr.end());

	CPPUNIT_ASSERT(false == IsIteartorInList(arr,it_end));
}
