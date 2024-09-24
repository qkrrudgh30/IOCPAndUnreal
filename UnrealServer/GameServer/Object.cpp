#include "pch.h"
#include "Object.h"

USObject::USObject()
{
	ObjectInfo = new Protocol::ObjectInfo();
	PosInfo = new Protocol::PosInfo();
	ObjectInfo->set_allocated_pos_info(PosInfo);
}

USObject::~USObject()
{
	delete ObjectInfo;
}
