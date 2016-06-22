#pragma once

#include "DetectionUnit.hpp"

class DetectionUnitFactory
{
public:
	static shared_ptr<DetectionUnit> CreateUnitFromTree(const wptree& wpt);
};
