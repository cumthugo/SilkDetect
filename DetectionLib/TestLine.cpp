#include "TestLine.hpp"



ptree TestLine::GetTree() const
{

	ptree pt = NamedItem::GetTree();
	foreach(const DetectionProgram& tp,*this)
	{
		pt.add_child("TestPrograms.TestProgram",tp.GetTree());
	}
	return pt;
}

void TestLine::ReadFromTree( const wptree& wpt )
{
	NamedItem::ReadFromTree(wpt);
	if(wpt.find(L"TestPrograms") != wpt.not_found())
	{
		foreach(const wptree::value_type& v, wpt.get_child(L"TestPrograms"))
		{
			DetectionProgram tp;
			tp.ReadFromTree(v.second);
			push_back(tp);
		}
	}
	
}

bool operator==( const TestLine& lhs, const TestLine& rhs )
{
	if(lhs.Name != rhs.Name) return false;
	TestLine::const_iterator left_pos,right_pos;
	for (left_pos = lhs.begin(),right_pos = rhs.begin();left_pos != lhs.end();++left_pos,++right_pos)
	{
		if(right_pos == rhs.end()) return false;
		if(*left_pos != *right_pos) return false;

	}
	if(right_pos != rhs.end()) return false;
	return true;
}

bool operator!=( const TestLine& lhs, const TestLine& rhs )
{
	return !(lhs == rhs);
}

ostream& operator<<( ostream& o, const TestLine& rhs )
{
	o <<"\nTestLine Name: " << rhs.Name;
	foreach(const DetectionProgram& tp,rhs)
	{
		o << tp;
	}
	return o;
}