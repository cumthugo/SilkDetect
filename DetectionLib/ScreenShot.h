#pragma once

#include "MyLib.hpp"
#include "DetectionUnit.hpp"


class ScreenShot
{
public:
	ScreenShot():itsFolderPath(""),itsMaxNumber(0){}
	ScreenShot(const string& folderPath, int N):itsFolderPath(folderPath),itsMaxNumber(N){}
	void Save(const string& unitName, IplImage_Ptr img, shared_ptr<DetectionUnit> du);
	void Init(const string& folderPath, int N)
	{
		itsFolderPath = folderPath;
		itsMaxNumber = N;
	}
private:
	bool processFolder(const string& p, shared_ptr<DetectionUnit> du);
	string itsFolderPath;
	int itsMaxNumber;
};