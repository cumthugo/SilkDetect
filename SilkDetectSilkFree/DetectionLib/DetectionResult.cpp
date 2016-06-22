#include "DetectionResult.hpp"
#include <boost/lexical_cast.hpp>

class EnglishResultFactory : public ResultFactory
{
public:
	virtual string GetPassString() const { return "Pass!";}
	virtual string GetPedestalErrorString() const { return "Pedestal Not Find!";}
	virtual string GetSilkErrorString() const { return "Silk Error!";}
	virtual string GetLockErrorString() const { return "Lock Error!";}
	virtual string GetBlueBoxErrorString() const { return "Blue Box Error!";}
};

class ChineseResultFactory : public ResultFactory
{
public:
	virtual string GetPassString() const { return "ͨ��!";}
	virtual string GetPedestalErrorString() const { return "δ�ں�ɫ�������ҵ�����!";}
	virtual string GetSilkErrorString() const { return "˿ӡλ�ô���!";}
	virtual string GetLockErrorString() const { return "����λ�ô���";}
	virtual string GetBlueBoxErrorString() const { return "��ɫ��λ�ô���!";}
};

shared_ptr<ResultFactory> ResultFactory::GetInstance()
{
	return shared_ptr<ResultFactory>(new ChineseResultFactory);
}



string ReportItem::GetReportString() const
{
	string passStr = Pass ? "P" : "F";
	return string(Unit + "_" + Name + "\t\tBOOL\t\t\t" + passStr + "\t\t1\t" + boost::lexical_cast<string>(Time));
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
