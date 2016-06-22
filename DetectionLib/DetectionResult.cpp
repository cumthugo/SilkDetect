#include "DetectionResult.hpp"


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
	virtual string GetPassString() const { return "通过!";}
	virtual string GetPedestalErrorString() const { return "未在红色区域中找到底座!";}
	virtual string GetSilkErrorString() const { return "丝印位置错误!";}
	virtual string GetLockErrorString() const { return "锁扣位置错误";}
	virtual string GetBlueBoxErrorString() const { return "蓝色条位置错误!";}
};

shared_ptr<ResultFactory> ResultFactory::GetInstance()
{
	return shared_ptr<ResultFactory>(new ChineseResultFactory);
}