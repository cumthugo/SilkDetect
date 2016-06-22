#pragma once

#include "MyLib.hpp"

#include "TestProgram.hpp"


class TestLine : public list<DetectionProgram>, public NamedItem
{
public:
	TestLine(){}
	TestLine(const string& LineName):NamedItem(LineName){}
	//–Ú¡–ªØ
	virtual ptree GetTree() const;
	virtual void ReadFromTree(const wptree& wpt);
};


bool operator==(const TestLine& lhs, const TestLine& rhs);
bool operator!=(const TestLine& lhs, const TestLine& rhs);
ostream& operator<<(ostream& o, const TestLine& rhs);