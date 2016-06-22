#include "DetectionUnitFactory.hpp"

#include "FrontDetectionUnit.hpp"
#include "BackDetectionUnit.hpp"
#include "HardLockDetectionUnit.hpp"
#include "NoLockDetectionUnit.hpp"

shared_ptr<DetectionUnit> DetectionUnitFactory::CreateUnitFromTree( const wptree& wpt )
{
	shared_ptr<DetectionUnit> detection_unit;
	int class_type = wpt.get<int>(L"Type");
	/*if(class_type == FrontDetectionUnit::TYPE_ID)
		detection_unit =  shared_ptr<DetectionUnit>(new FrontDetectionUnit);
	else
		detection_unit =  shared_ptr<DetectionUnit>(new BackDetectionUnit);*/
	switch (class_type)
	{
	case FrontDetectionUnit::TYPE_ID:
		detection_unit =  shared_ptr<DetectionUnit>(new FrontDetectionUnit);
		break;
	case BackDetectionUnit::TYPE_ID:
		detection_unit = shared_ptr<DetectionUnit>(new BackDetectionUnit);
		break;
	case HardLockDetectionUnit::TYPE_ID:
		detection_unit = shared_ptr<DetectionUnit>(new HardLockDetectionUnit);
		break;
	case NoLockDetectionUnit::TYPE_ID:
		detection_unit = shared_ptr<DetectionUnit>(new NoLockDetectionUnit);
		break;
	}
	detection_unit->ReadFromTree(wpt);
	return detection_unit;
}