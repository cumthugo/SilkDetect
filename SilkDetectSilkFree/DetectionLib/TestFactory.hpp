#pragma once

#include "MyLib.hpp"

#include "TestLine.hpp"

class TestFactory : public list<TestLine>
{
public:
	TestFactory(){}
	//–Ú¡–ªØ
	virtual ptree GetTree() const;
	virtual void ReadFromTree(const wptree& wpt);
};

bool operator==(const TestFactory& lhs, const TestFactory& rhs);
bool operator!=(const TestFactory& lhs, const TestFactory& rhs);
ostream& operator<<(ostream& o, const TestFactory& rhs);