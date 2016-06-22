#pragma once

#include "MyLib.hpp"

struct DetectionResult
{
	bool IsPass;
	string ErrorString;
	IplImage_Ptr ResultImage;
};

class ResultFactory
{
public:
	virtual ~ResultFactory(){}
	virtual string GetPassString() const = 0;
	virtual string GetPedestalErrorString() const = 0;
	virtual string GetSilkErrorString() const = 0;
	virtual string GetLockErrorString() const = 0;
	virtual string GetBlueBoxErrorString() const = 0;
	static shared_ptr<ResultFactory> GetInstance();
};