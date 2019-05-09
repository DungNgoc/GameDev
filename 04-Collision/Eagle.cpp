#include "Eagle.h"



CEagle::CEagle()
{
	isLeft = true;
}

void CEagle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + EAGLE_BBOX_WIDTH;
	bottom = y + EAGLE_BBOX_HEIGHT;
}

void CEagle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	////
	//// TO-DO: make sure BUTERFLY can interact with the world and to each of them too!
	//// 
	x += dx;
	y += dy;
	//
	
	LimitPos(limitX1, limitX2);
}
void CEagle::LimitPos(int limitX1, int limitX2)
{
	if(y<=110 && x<= limitX1 ){
		vx = -EAGLE_FLY_SPEED;
		vy = EAGLE_FLY_SPEED;
	}
	if (y >= 110)
	{
		vx = EAGLE_FLY_SPEED;
		vy = 0;
	}
	if (vx > 0 && x >= limitX2  ) {
		x = limitX1;
		y = 45;
	/*	vx = -EAGLE_FLY_SPEED;
		vy = -EAGLE_FLY_SPEED;*/
	}
	/*if (vx < 0 && x < limitX1) {
		x = limitX1, vx = -vx;
		vy = -EAGLE_FLY_SPEED;
	}*/
}
void CEagle::Render()
{
	
	
}

void CEagle::Render(ViewPort * viewport)
{
	/*if (y == 55)
		isLeft = true;*/
	int ani = EAGLE_ANI_RIGHT;
	
	//if (state == PANTHER_STATE_DIE) {
	//	ani = PANTHER_ANI_DIE;
	//}
	
	int alpha = 255;
	if (vx < 0)
		isLeft = false;
	else
	{
		isLeft = true;
	}
	animations[ani]->Render(viewport, x, y, alpha, isLeft);

	RenderBoundingBox(viewport);
}


CEagle::~CEagle()
{
}
