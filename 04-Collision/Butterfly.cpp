#include "Butterfly.h"


CButterfly::CButterfly()
{
}

void CButterfly::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x-1;
	top = y;
	right = x + BUTTERFLY_BBOX_WIDTH;
	bottom = y + BUTTERFLY_BBOX_HEIGHT;
}

void CButterfly::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure BUTERFLY can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;

	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}
}

void CButterfly::Render()
{
}

void CButterfly::Render(ViewPort * viewport)
{
	int ani = BUTTERFLY_ANI_RIGHT;
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
	
	if(GetEnable())
		animations[ani]->Render(viewport, x, y, alpha, isLeft);

	RenderBoundingBox(viewport);
}

CButterfly::~CButterfly()
{
}
