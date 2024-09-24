#include "pch.h"
#include "Actor.h"

USActor::USActor()
{
	ObjectInfo->set_object_type(Protocol::ObjectType::OBJECT_TYPE_CREATURE);
}

USActor::~USActor()
{
}
