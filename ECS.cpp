#include "ECS.h"

void Entity::addGroup(Group mGroup)
{
	groupBitset[mGroup] = true;//punem 1 la biti ca sa stim ca este OK
	manager.AddToGroup(this, mGroup);
}