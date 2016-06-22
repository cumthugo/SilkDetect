#pragma once

#include "DetectionUnit.hpp"
#include "ScreenShot.h"


class DetectionProgram : public list<shared_ptr<DetectionUnit> >, public NamedItem
{
public:
	DetectionProgram(){ UnLock();}
	DetectionProgram(const string& ProgramName):NamedItem(ProgramName){ UnLock();}

	void CopyOf(const DetectionProgram& dp);

	//序列化
	virtual ptree GetTree() const;
	virtual void ReadFromTree(const wptree& wpt);
	// operators
	void UpItem(iterator pos);

	void Detect(IplImage_Ptr sourceImage,DetectionResult& result);

	//add in 2015/04/28
	void SetScreenShot(const string& folderPath, int N){ itsScreenShot.Init(folderPath,N);}
	ScreenShot itsScreenShot;
	
	//function lock
	void UnLock(){lock_iter = end();}
	bool IsLock(){ return lock_iter != end(); }
	void Lock(iterator iter) {lock_iter = iter;}
	//shared_ptr<DetectionUnit> GetLockDetectUnit() { return *lock_iter;} //需要重构
private:
	iterator lock_iter;
	IplImage_Ptr GetSubImage(IplImage_Ptr sourceImage, iterator& it);
	CvRect GetROIRect(IplImage_Ptr sourceImage, iterator& it);
	void CopyResult2Source(IplImage_Ptr sourceResultImage, iterator it, IplImage_Ptr resultImage);
};


bool operator==(const DetectionProgram& lhs, const DetectionProgram& rhs);
bool operator!=(const DetectionProgram& lhs, const DetectionProgram& rhs);
ostream& operator<<(ostream& o, const DetectionProgram& rhs);