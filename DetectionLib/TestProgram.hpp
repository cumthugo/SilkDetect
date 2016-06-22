#pragma once

#include "MyLib.hpp"

#include "TestUnit.hpp"


class DetectionProgram : public list<TestUnit>, public NamedItem
{
public:
	// create
	DetectionProgram(){}
	DetectionProgram(const string& ProgramName):NamedItem(ProgramName){}
	//–Ú¡–ªØ
	virtual ptree GetTree() const;
	virtual void ReadFromTree(const wptree& wpt);
	// operators
	void UpItem(const string& UnitName);
	void UpItem(iterator pos);
};


bool operator==(const DetectionProgram& lhs, const DetectionProgram& rhs);
bool operator!=(const DetectionProgram& lhs, const DetectionProgram& rhs);
ostream& operator<<(ostream& o, const DetectionProgram& rhs);