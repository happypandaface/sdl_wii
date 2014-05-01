#ifndef _OBJECT_HOLDER_H_
#define _OBJECT_HOLDER_H_

class ObjectHolder;
struct ObjectIterator;
struct ObjectLink;

#include "base_object.h"


class ObjectHolder
{
	public:
		ObjectHolder();
		~ObjectHolder();
		struct ObjectIterator *getIterator();
		void resetIterator(struct ObjectIterator *oi);
		void destroyIterator(struct ObjectIterator *oi);
		int hasNext(struct ObjectIterator* oi);
		BaseObject *next(struct ObjectIterator* oi);
		void clear();
		void destroyObjs();
		int addObject(BaseObject *bo);
		int removeObject(BaseObject *bo, int isDeleting);
	private:
		struct ObjectLink *firstLink;
};
#endif