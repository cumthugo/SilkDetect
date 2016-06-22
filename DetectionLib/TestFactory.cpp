#include "TestFactory.hpp"


ptree TestFactory::GetTree() const
{
	ptree pt;
	foreach(const TestLine& tl,*this)
	{
		pt.add_child("TestLines.TestLine",tl.GetTree());
	}
	return pt;
}

void TestFactory::ReadFromTree( const wptree& wpt )
{
	if(wpt.find(L"TestLines") != wpt.not_found())
	{
		foreach(const wptree::value_type& v, wpt.get_child(L"TestLines"))
		{
			TestLine tl;
			tl.ReadFromTree(v.second);
			push_back(tl);
		}
	}
}

bool operator==( const TestFactory& lhs, const TestFactory& rhs )
{
	TestFactory::const_iterator left_pos,right_pos;
	for (left_pos = lhs.begin(),right_pos = rhs.begin();left_pos != lhs.end();++left_pos,++right_pos)
	{
		if(right_pos == rhs.end()) return false;
		if(*left_pos != *right_pos) return false;

	}
	if(right_pos != rhs.end()) return false;
	return true;
}

bool operator!=( const TestFactory& lhs, const TestFactory& rhs )
{
	return !(lhs == rhs);
}

ostream& operator<<( ostream& o, const TestFactory& rhs )
{
	o <<"\nTestFactory: ";
	foreach(const TestLine& tl,rhs)
	{
		o << tl;
	}
	return o;
}