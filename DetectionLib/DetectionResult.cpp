#include "DetectionResult.hpp"
#include <boost/lexical_cast.hpp>

class EnglishResultFactory : public ResultFactory
{
public:
	virtual string GetErrorStringByErrorCode(int ecode) const 
	{
		switch (ecode)
		{
		case RESULT_PASS:
			return "Pass!";
		case RESULT_FAIL_CABLE:
			return "Cable Not Found!";
		case RESULT_FAIL_PEDESTAL:
			return "Pedestal Not Found!";
		case RESULT_FAIL_SILK:
			return "Silk Error!";
		case RESULT_FAIL_LOCK:
			return "Lock Error!";
		case RESULT_FAIL_AUTH:
			return "Software Not Register!";
		case RESULT_FAIL_CAMERA:
			return "Camera Not Found!";
		case RESULT_FAIL_BAR_CODE:
			return "Please Scan BarCode!";
		default:
			return "Unknown Error!";
		}
	}
};

class ChineseResultFactory : public ResultFactory
{
public:
	virtual string GetErrorStringByErrorCode(int ecode) const 
	{
		switch (ecode)
		{
		case RESULT_PASS:
			return "通过!";
		case RESULT_FAIL_CABLE:
			return "排线装配错误!\n请装配排线！";
		case RESULT_FAIL_PEDESTAL:
			return "未在红色区域中找到底座!";
		case RESULT_FAIL_SILK:
			return "丝印装配错误!\n请拆下排线";
		case RESULT_FAIL_LOCK:
			return "锁扣装配错误!";
		case RESULT_FAIL_AUTH:
			return "无法使用检测程序，软件未注册!";
		case RESULT_FAIL_CAMERA:
			return "获取图片错误！请检查摄像头的连接!";
		case RESULT_FAIL_BAR_CODE:
			return "请扫条码!";
		default:
			return "未知错误!";
		}
	}
};

shared_ptr<ResultFactory> ResultFactory::GetInstance()
{
	return shared_ptr<ResultFactory>(new ChineseResultFactory);
}


string ReportItem::GetReportString() const
{
	string passStr = Pass ? "P" : "F";
	return string(Unit + "_" + Name + "\t\tBOOL\t\t" + passStr + "\t\t1\t" + boost::lexical_cast<string>(Time));
}

void DetectionResult::AddItemReport( const string& unit, const string& name, bool pass, long time )
{
	shared_ptr<ReportItem> report = make_shared<ReportItem>();
	report->Unit = unit;
	report->Name = name;
	report->Pass = pass;
	report->Time = time;
	Report.push_back(report);
}

void DetectionResult::AddUnitReport()
{
	shared_ptr<ReportUnit> report = make_shared<ReportUnit>();
	Report.push_back(report);
}
