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

	//
	// TO-DO: make sure SOLDIER can interact with the world and to each of them too!
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
	animations[ani]->Render(viewport, x, y, alpha, isLeft);

	RenderBoundingBox(viewport);
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

