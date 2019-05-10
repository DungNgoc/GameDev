#include "Eagle.h"



CEagle::CEagle():CEnemy(1)
{
	//isLeft = true;
	damage = 1;
	point = 100;
}

void CEagle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	//if (ani->getCurrentFrame() == EAGLE_ANI_1)
	{
		left = x;
		top = y;
		right = x + EAGLE_BBOX_WIDTH;
		bottom = y + EAGLE_BBOX_HEIGHT;
	}
	//else if (ani->getCurrentFrame() == EAGLE_ANI_2)
	/*{
		left = x;
		top = y;
		right = x + 17;
		bottom = y + 25;
	}*/
}

void CEagle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CEnemy::Update(dt);
	x += dx;
	y += dy;

	
	LimitPos(limitX1, limitX2);
}
void CEagle::LimitPos(int limitX1, int limitX2)
{
	if(y<110 && x<= limitX1 ){
		vx = -EAGLE_FLY_SPEED;
		vy = EAGLE_FLY_SPEED;
	}
	
	if (y >= 110)
	{
		if (vx > 0 && x >= limitX2) {
			x = limitX2;
			vx = -EAGLE_FLY_SPEED;
			vy = 0;
		}else {
			vx = EAGLE_FLY_SPEED;
			vy = 0;
		}
		
	}

}
void CEagle::Render()
{
	
	
}

void CEagle::Render(ViewPort * viewport)
{
	int ani = EAGLE_ANI_RIGHT;
	
	
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
