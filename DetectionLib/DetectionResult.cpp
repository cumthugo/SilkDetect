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