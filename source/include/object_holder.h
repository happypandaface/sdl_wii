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
		int addObject(BaseObject *bo);
	private:
		struct ObjectLink *firstLink;
};
#endif