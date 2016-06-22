#pragma once

#include "MyLib.hpp"
#include <Windows.h>

class ReportLine
{
public:
	virtual string GetReportString() const = 0;
};

struct ReportItem : public ReportLine
{
public:
	string Unit;
	string Name;
	bool Pass;
	long Time;
	string GetReportString() const;
};

struct ReportUnit : public ReportLine
{
public:
	string GetReportString() const { return "";}
};


typedef shared_ptr<ReportLine> ReportLine_Ptr;
typedef list<ReportLine_Ptr> ReportLineList;


class Clock_MS
{
public:
	Clock_MS():_1_complete(false),_2_complete(false){}
	void Start(){ _begin = GetTickCount(); _1_complete = true; }
	void Stop()
	{
		if(_1_complete)
		{
			_end = GetTickCount();
			_2_complete = true;
		}
	}
	long GetTime()
	{ 
		if(_2_complete)
			return _end - _begin;
		else
			return 0;
	}
	void Reset()
	{
		_1_complete = _2_complete = false;
	}
private:
	long _begin;
	long _end;
	bool _1_complete;
	bool _2_complete;
};


#define RESULT_PASS 0
#define RESULT_FAIL_PEDESTAL -1
#define RESULT_FAIL_CABLE -2
#define RESULT_FAIL_SILK -3
#define RESULT_FAIL_LOCK -4
#define RESULT_FAIL_CAMERA -5
#define RESULT_FAIL_AUTH -6
#define RESULT_FAIL_UNKNOWN -7
#define RESULT_FAIL_BAR_CODE -8


struct DetectionResult
{
	ReportLineList Report;
	//bool IsPass;
	bool IsPass() { return RESULT_PASS == ErrorCode;}
	int ErrorCode;
	IplImage_Ptr ResultImage;
	void AddItemReport(const string& unit, const string& name, bool pass, long time);
	void AddUnitReport();
};

class ResultFactory
{
public:
	virtual ~ResultFactory(){}	
	virtual string GetErrorStringByErrorCode(int ecode) const = 0;
	static shared_ptr<ResultFactory> GetInstance();
};