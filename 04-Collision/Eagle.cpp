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
	vx = - EAGLE_FLY_SPEED;
	vy = EAGLE_FLY_SPEED;
	
	if (y >= 90)
	{
		vx = EAGLE_FLY_SPEED;
		vy = 0;
	}///*if (vx < 0 && x < 0) {
	//	x = 0; vx = -vx;
	//}

	//if (vx > 0 && x > 290) {
	//	x = 290; vx = -vx;
	//}*/
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
