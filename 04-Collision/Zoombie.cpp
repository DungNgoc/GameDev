#include "Zoombie.h"



CZoombie::CZoombie():CEnemy(1)
{
	damage = 1;
	point = 100;
}


CZoombie::~CZoombie()
{
}


void CZoombie::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ZOOMBIE_STATE_DIE:
		vx = 0.1;
		vy = 0;
		break;
	case ZOOMBIE_STATE_WALKING:
		vx = -ZOOMBIE_WALKING_SPEED;
	}
}

void CZoombie::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + ZOOMBIE_BBOX_WIDTH;
	bottom = y + ZOOMBIE_BBOX_HEIGHT;
}

void CZoombie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CEnemy::Update(dt);
	x += dx;
	y += dy;

	LimitPos(limitX1, limitX2);
}

void CZoombie::Render()
{
}

void CZoombie::Render(ViewPort * viewport)
{
	int ani = ZOOMBIE_ANI_WALKING;
	isLeft = true;
	if (state == ZOOMBIE_STATE_DIE) {
		//ani = ZOOMBIE_ANI_DIE;
	}
	int alpha = 255;
	if (untouchable)   alpha = 255;
	if (vx < 0)
		isLeft = false;
	else
	{
		isLeft = true;
	}
	/*if(GetDead())*/
	CEnemy::Render(viewport);
	if (GetEnable())
		animations[ani]->Render(viewport, x, y, alpha, isLeft);
	//if(GetEnable())
	RenderBoundingBox(viewport);
}

void CZoombie::LimitPos(int limitX1, int limitY1)
{
	if (vx < 0 && x < limitX1) {
		x = limitX1; vx = -vx;
	}

	if (vx > 0 && x > limitX2) {
		x = limitX2; vx = -vx;
	}
}
