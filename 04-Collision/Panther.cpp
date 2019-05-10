#include "Panther.h"



void CPanther::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

	left = x;
	top = y;
	right = x + PANTHER_BBOX_WIDTH;
	bottom = y + PANTHER_BBOX_HEIGHT;

	//if (state == PANTHER_STATE_DIE)
		//bottom = y + SOLDIER_BBOX_HEIGHT_DIE;
	//else
	//	bottom = y + SOLDIER_BBOX_HEIGHT;
}

void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	CEnemy::Update(dt);
	x += dx;
	y += dy;

	LimitPos(limitX1, limitX2);
}
void CPanther::LimitPos(int limitX1, int limitX2)
{
	if (vx < 0 && x < limitX1) {
		x = limitX1; vx = -vx;
	}

	if (vx > 0 && x > limitX2) {
		x = limitX2; vx = -vx;
	}
}
void CPanther::Render() {}
void CPanther::Render(ViewPort * viewport)
{
	int ani = PANTHER_ANI_WALKING;
	isLeft = true;
	//if (state == PANTHER_STATE_DIE) {
	//	ani = PANTHER_ANI_DIE;
	//}
	int alpha = 255;
	if (untouchable)   alpha = 255;
	if (vx < 0)
		isLeft = false;
	else
	{
		isLeft = true;
	}
	CEnemy::Render(viewport);
	if (GetEnable())
		animations[ani]->Render(viewport, x, y, alpha, isLeft);

	RenderBoundingBox(viewport);
}

CPanther::CPanther() :CEnemy(1)
{
	damage = 1;
	point = 100;
}

CPanther::~CPanther()
{
}

void CPanther::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	/*case PANTHER_STATE_DIE:
		y += SOLDIER_BBOX_HEIGHT - SOLDIER_BBOX_HEIGHT_DIE + 1;
		vx = 0.1;
		vy = 0;
		break;*/
	case PANTHER_STATE_WALKING:
		vx = -PANTHER_WALKING_SPEED;
	}

}

