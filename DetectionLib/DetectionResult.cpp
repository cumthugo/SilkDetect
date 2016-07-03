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
	virtual string GetPassString() const { return "Í¨¹ý!";}
	virtual string GetPedestalErrorString() const { return "Î´ÔÚºìÉ«ÇøÓòÖÐÕÒµ½µ××ù!";}
	virtual string GetSilkErrorString() const { return "Ë¿Ó¡Î»ÖÃ´íÎó!";}
	virtual string GetLockErrorString() const { return "Ëø¿ÛÎ»ÖÃ´íÎó";}
	virtual string GetBlueBoxErrorString() const { return "À¶É«ÌõÎ»ÖÃ´íÎó!";}
};

static DetectionResult err_detectresult;

DetectionResult& FirstErrorResult( DetectionResultList& result_list )
{
	if (result_list.size() > 0)
		return (*result_list.begin());

	return err_detectresult; /* must not return here */
}

DetectionResultList NormalResultList( const DetectionResultList& result_list )
{
	DetectionResultList ret_list(result_list);
	if (ret_list.size() > 0)
		ret_list.pop_front();
	return ret_list;
}

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
