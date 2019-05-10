#include "Soldier.h"


void CSoldier::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

	left = x;
	top = y;
	right = x + SOLDIER_BBOX_WIDTH;
	bottom = y + SOLDIER_BBOX_HEIGHT;
	//if (state == SOLDIER_STATE_DIE)
	//	bottom = y + SOLDIER_BBOX_HEIGHT_DIE;
	//else
	//	bottom = y + SOLDIER_BBOX_HEIGHT;
}

void CSoldier::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

	CEnemy::Update(dt);
	x += dx;
	y += dy;
	
	LimitPos(limitX1, limitX2);

}
void CSoldier::Render(){}
void CSoldier::Render(ViewPort * viewport)
{
	int ani = SOLDIER_ANI_WALKING;
	isLeft = true;
	if (state == SOLDIER_STATE_DIE) {
		ani = SOLDIER_ANI_DIE;
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
	if(GetEnable())
		animations[ani]->Render(viewport, x, y, alpha, isLeft);
	//if(GetEnable())
	RenderBoundingBox(viewport);
}

void CSoldier::LimitPos(int limitX1, int limitX2)
{
	if (vx < 0 && x < limitX1) {
		x = limitX1; vx = -vx;
	}

	if (vx > 0 && x > limitX2) {
		x = limitX2; vx = -vx;
	}
}

CSoldier::CSoldier():CEnemy(1)
{
	
	damage = 1;
	point = 100;
}


CSoldier::~CSoldier()
{
}

void CSoldier::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SOLDIER_STATE_DIE:
		//y += SOLDIER_BBOX_HEIGHT - SOLDIER_BBOX_HEIGHT_DIE + 1;
		vx = 0.1;
		vy = 0;
		break;
	case SOLDIER_STATE_WALKING:
		vx = -SOLDIER_WALKING_SPEED;
	}

}




