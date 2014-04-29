#include "gravity.h"
#include "player.h"
#include <typeinfo>

Gravity::Gravity()
{
}
Gravity::~Gravity()
{
}
void Gravity::setStrength(float s)
{
	strength = s;
}
void Gravity::update(ObjectHolder *objHolder, float delta)
{
	ObjectIterator *objIter = objHolder->getIterator();
	BaseObject *curr;
	while(objHolder->hasNext(objIter))
	{
		curr = objHolder->next(objIter);
		if (curr->checkType(TYP_HAS_GRAV))
		{
			curr->doGravity(strength, delta);
		}
		/* old:
		Player *plr = dynamic_cast<Player*>(curr);
		if (plr)
		{
			plr->doGravity(strength, delta);
		}
		*/
	}
	objHolder->destroyIterator(objIter);
}