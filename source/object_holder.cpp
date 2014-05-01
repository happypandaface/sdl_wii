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
void ObjectHolder::clear()
{
	while (firstLink != NULL)
	{
		struct ObjectLink *temp = firstLink->next;
		// TODO: delete objs if told
		delete firstLink;
		firstLink = temp;
	}
}
int ObjectHolder::removeObject(BaseObject *bo, int isDeleting)
{
	struct ObjectLink *last = NULL;
	struct ObjectLink *curr = firstLink;
	while(curr != NULL)
	{
		if (curr->obj == bo)
			break;
		else
		{
			last = curr;
			curr = curr->next;
		}
	}
	if (curr == NULL)// didn't find the object
		return -1;
	if (last == NULL)// it was the first object
	{
		struct ObjectLink *temp = firstLink;
		firstLink = firstLink->next;
		if (isDeleting > 0)
			delete temp->obj;
		delete temp;
		return 1;
	}
	// this is the last option, it's in the list but not the first
	last->next = curr->next;
	if (isDeleting > 0)
		delete curr->obj;
	delete curr;
	return 1;
}
int ObjectHolder::addObject(BaseObject *bo)
{
	struct ObjectLink *newLink = new ObjectLink;
	newLink->obj = bo;
	newLink->next = NULL;
	struct ObjectLink *last = NULL;
	struct ObjectLink *curr = firstLink;
	while (curr != NULL)
	{
		// sorting stuff here
		if (curr->obj->getLayer() > newLink->obj->getLayer())
			break;
		last = curr;
		curr = curr->next;
	}
	if (last == NULL)// this means it was the first link
	{
		firstLink = newLink;
		newLink->next = curr;
	}else
	{
		if (curr)
			newLink->next = curr;
		last->next = newLink;
	}
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