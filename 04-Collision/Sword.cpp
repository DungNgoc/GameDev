#include "Sword.h"



Sword::Sword()
{
	isLeft = true;
	AddAnimation(4001);

}
void Sword::ResetAnimation()
{
	resetAni(0);
	/*resetAni(1);
	resetAni(2);*/
	
}
void Sword::SetPosition(float x, float y, bool Issit)
{

	if (Issit == false)
	{
		if (!isLeft)
		{
			x -= NINJA_SET_POSITION_HIT_X;
			y += NINJA_SET_POSITION_HIT_Y;
		}
		else
		{
			x += NINJA_SET_POSITION_HIT_X;
			y += NINJA_SET_POSITION_HIT_Y;
		}
		
	}
	else
	{
		if (!isLeft)
		{
			x -= NINJA_SET_POSITION_SIT_X;
			y += NINJA_SET_POSITION_SIT_Y;
		}
		else
		{
			x += NINJA_SET_POSITION_SIT_X;
			y += NINJA_SET_POSITION_SIT_Y;
		}
	}
	
	//else
	//	x -= MORNINGSTAR_SET_POSITION_X;
	CGameObject::SetPosition(x, y);
}
void Sword::Render()
{
}

void Sword::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}


void Sword::Render(ViewPort * viewport)
{
	int alpha = 255;
	animations[0]->Render(viewport, x, y, alpha, isLeft);
}


Sword::~Sword()
{
}
