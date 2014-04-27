#include "object_holder.h"

struct ObjectIterator
{
	struct ObjectLink *currObjLnk;
};

struct ObjectLink
{
	BaseObject *obj;
	struct ObjectLink *next;
};

ObjectHolder::ObjectHolder()
{
	firstLink = NULL;
}
ObjectHolder::~ObjectHolder()
{
	while (firstLink != NULL)
	{
		struct ObjectLink *temp = firstLink->next;
		delete firstLink->obj;
		delete firstLink;
		firstLink = temp;
	}
}
int ObjectHolder::addObject(BaseObject *bo)
{
	struct ObjectLink *newLink = new ObjectLink;
	newLink->obj = bo;
	if (firstLink != NULL)
	{
		newLink->next = firstLink;
	}else
		newLink->next = NULL;
	firstLink = newLink;
	return 1;
}
struct ObjectIterator *ObjectHolder::getIterator()
{
	struct ObjectIterator *oi = new ObjectIterator;
	resetIterator(oi);
	return oi;
}
void ObjectHolder::resetIterator(struct ObjectIterator *oi)
{
	oi->currObjLnk = firstLink;
}
void ObjectHolder::destroyIterator(struct ObjectIterator *oi)
{
	delete oi;
}
int ObjectHolder::hasNext(struct ObjectIterator* oi)
{
	if (oi->currObjLnk != NULL)
		return 1;
	return 0;
}
BaseObject *ObjectHolder::next(struct ObjectIterator* oi)
{
	BaseObject *temp = oi->currObjLnk->obj;
	oi->currObjLnk = oi->currObjLnk->next;
	return temp;
}