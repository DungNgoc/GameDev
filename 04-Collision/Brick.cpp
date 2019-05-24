#include "Brick.h"

void CBrick::Render()
{
	//animations[0]->Render(x, y);
	
}

void CBrick::Render(ViewPort * viewport)
{
	//RenderBoundingBox(viewport);
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y ;
	r = x + width;
	b = y + height;
}

CBrick::CBrick()
{
}

CBrick::~CBrick()
{
}

