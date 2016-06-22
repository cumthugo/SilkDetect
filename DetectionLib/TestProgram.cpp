#include "TestProgram.hpp"



void DetectionProgram::UpItem( const string& UnitName )
{
	iterator pos = find_if(begin(),end(),bind2nd(NamedItem_Find_PD<TestUnit>(),UnitName));
	if (pos != end())
	{
		//exchange
		if(pos != begin())
		{
			iterator current_pos = pos--;
			std::swap(*pos,*current_pos);
		}
	}
}

void DetectionProgram::UpItem( iterator pos )
{
	if(pos != begin())
	{
		iterator current_pos = pos--;
		std::swap(*pos,*current_pos);
	}
}

ptree DetectionProgram::GetTree() const
{
	ptree pt = NamedItem::GetTree();
	foreach(const TestUnit& tu,*this)
	{
		pt.add_child("TestUnits.TestUnit",tu.GetTree());
	}
	return pt;
}

void DetectionProgram::ReadFromTree( const wptree& wpt )
{
	NamedItem::ReadFromTree(wpt);
	if(wpt.find(L"TestUnits") != wpt.not_found())
	{
		foreach(const wptree::value_type& v, wpt.get_child(L"TestUnits"))
		{
			TestUnit tu;
			tu.ReadFromTree(v.second);
			push_back(tu);
		}
	}
}

bool operator==( const DetectionProgram& lhs, const DetectionProgram& rhs )
{
	if(lhs.Name != rhs.Name) return false;
	DetectionProgram::const_iterator left_pos,right_pos;
	for (left_pos = lhs.begin(),right_pos = rhs.begin();left_pos != lhs.end();++left_pos,++right_pos)
	{
		if(right_pos == rhs.end()) return false;
		if(*left_pos != *right_pos) return false;
		
	}
	if(right_pos != rhs.end()) return false;
	return true;
}

bool operator!=( const DetectionProgram& lhs, const DetectionProgram& rhs )
{
	return !(lhs == rhs);
}

ostream& operator<<( ostream& o, const DetectionProgram& rhs )
{
	o <<"\nTestProgram Name: " << rhs.Name;
	foreach(const TestUnit& tu,rhs)
	{
		o << tu;
	}
	return o;
}