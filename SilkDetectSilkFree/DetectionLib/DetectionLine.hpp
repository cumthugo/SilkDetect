#pragma once

#include "DetectionProgram.hpp"

class DetectionLine : public list<shared_ptr<DetectionProgram> >, public NamedItem
{
public:
	DetectionLine(){}
	DetectionLine(const string& LineName):NamedItem(LineName){}

	void CopyOf(const DetectionLine& dl);


	//–Ú¡–ªØ
	virtual ptree GetTree() const;
	virtual void ReadFromTree(const wptree& wpt);
};

bool operator==(const DetectionLine& lhs, const DetectionLine& rhs);
bool operator!=(const DetectionLine& lhs, const DetectionLine& rhs);
ostream& operator<<(ostream& o, const DetectionLine& rhs);