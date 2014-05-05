#include "imgfx_split.h"
#include <iostream>

ImgFxSplit::ImgFxSplit(int x, int y, int w, int h)
{
	start.set(x, y);
	size.set(w, h);
	std::cout << start.toString() << size.toString() << "\n";
}

int ImgFxSplit::applyRect(SDL_Rect *src, SDL_Rect *dst)
{
	if (dst->x + dst->w < start.getX() ||
		dst->x > start.getX() + size.getX() ||
		dst->y + dst->h < start.getY() ||
		dst->y > start.getY() + size.getY())
		return 1;
	// horiz stuff
	if (dst->x < start.getX())
	{
		float distLeft = start.getX() - dst->x;
		src->x += distLeft;
		dst->x += distLeft;
		src->w -= distLeft;
		dst->w -= distLeft;
	}
	if (dst->x + dst->w > start.getX() + size.getX())
	{
		float distRight = (dst->x + dst->w) - (start.getX() + size.getX());
		dst->w -= distRight;
		src->w -= distRight;
	}
	// vert stuff
	if (dst->y < start.getY())
	{
		float distTop = start.getY() - dst->y;
		src->y += distTop;
		dst->y += distTop;
		src->h -= distTop;
		dst->h -= distTop;
	}
	if (dst->y + dst->h > start.getY() + size.getY())
	{
		float distBottom = (dst->y + dst->h) - (start.getY() + size.getY());
		dst->h -= distBottom;
		src->h -= distBottom;
	}
	return 0;
}