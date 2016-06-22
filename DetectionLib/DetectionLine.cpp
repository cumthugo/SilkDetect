#include "DetectionLine.hpp"


void DetectionLine::CopyOf( const DetectionLine& dl )
{
	Name = dl.Name;
	clear();
	foreach(const shared_ptr<DetectionProgram>& dp,dl)
	{
		shared_ptr<DetectionProgram> program = shared_ptr<DetectionProgram>(new DetectionProgram); 
		program->CopyOf(*dp);
		push_back(program);
	}
}

ptree DetectionLine::GetTree() const
{
	ptree pt = NamedItem::GetTree();
	foreach(const shared_ptr<DetectionProgram>& dp,*this)
	{
		pt.add_child("DetectionPrograms.DetectionProgram",dp->GetTree());
	}
	return pt;
}

void DetectionLine::ReadFromTree( const wptree& wpt )
{
	NamedItem::ReadFromTree(wpt);
	if(wpt.find(L"DetectionPrograms") != wpt.not_found())
	{
		foreach(const wptree::value_type& v, wpt.get_child(L"DetectionPrograms"))
		{
			shared_ptr<DetectionProgram> program = shared_ptr<DetectionProgram>(new DetectionProgram); 
			program->ReadFromTree(v.second);
			push_back(program);
		}
	}
}

bool operator==( const DetectionLine& lhs, const DetectionLine& rhs )
{
	return lhs.Name == rhs.Name && lhs.size() == rhs.size();
}

bool operator!=( const DetectionLine& lhs, const DetectionLine& rhs )
{
	return !(lhs == rhs);
}

ostream& operator<<( ostream& o, const DetectionLine& rhs )
{
	cout << rhs.Name << endl;
	return o;
}
