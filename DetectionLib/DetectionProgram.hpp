#pragma once

#include "DetectionUnit.hpp"


class DetectionProgram : public list<shared_ptr<DetectionUnit> >, public NamedItem
{
public:
	DetectionProgram(){}
	DetectionProgram(const string& ProgramName):NamedItem(ProgramName){}

	void CopyOf(const DetectionProgram& dp);

	//–Ú¡–ªØ
	virtual ptree GetTree() const;
	virtual void ReadFromTree(const wptree& wpt);
	// operators
	void UpItem(iterator pos);

	void Detect(IplImage_Ptr sourceImage,DetectionResult& result);
};


bool operator==(const DetectionProgram& lhs, const DetectionProgram& rhs);
bool operator!=(const DetectionProgram& lhs, const DetectionProgram& rhs);
ostream& operator<<(ostream& o, const DetectionProgram& rhs);