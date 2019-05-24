#include "Panther.h"
#include "Brick.h"


void CPanther::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

	left = x;
	top = y  ;
	right = x + PANTHER_BBOX_WIDTH;
	bottom = top + PANTHER_BBOX_HEIGHT;

}

void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (isEnable == true)
		vy += 0.000900 * dt;
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CBrick *>(coObjects->at(i)))
		{
			CBrick *brick = dynamic_cast<CBrick *>(coObjects->at(i));
			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			brick->GetBoundingBox(l2, t2, r2, b2);
			if (t1 <= b2 && b1 >= t2 && l1 <= r2 && r1 >= l2) {
				vy = -0.15;
			}
		}
	}
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
	//isLeft = true;
	
	int alpha = 255;
	if (untouchable)   alpha = 255;
	if (vx < 0)
		isLeft = false;
	else
	{
		isLeft = true;
	}
	//CEnemy::Render(viewport);
	if (GetEnable())
		animations[ani]->Render(viewport, x, y, alpha, isLeft);

	RenderBoundingBox(viewport);
}

CPanther::CPanther() :CEnemy(1)
{
	damage = 1;
	point = 100;
	vy = -0.15;
}

CPanther::~CPanther()
{
}

void CPanther::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	
	case PANTHER_STATE_WALKING:
		vx = -PANTHER_WALKING_SPEED;
	}

}

