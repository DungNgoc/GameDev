#include "Zoombie.h"
#include "Grid.h"


CZoombie::CZoombie():CEnemy(1)
{
	damage = 1;
	point = 200;
	zoombiesword = new CZoombieSword();
	zoombiesword->SetEnable(false);
	
}


CZoombie::~CZoombie()
{
}


void CZoombie::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ZOOMBIE_STATE_HIT:
		vx = 0;
		break;
	case ZOOMBIE_STATE_RUN:
		if (isLeft)
			vx = ZOOMBIE_WALKING_SPEED;
		else
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
	if (isEnable && !isDead) {
		timeDelay += dt;
		if (!zoombiesword->GetEnable() && state == ZOOMBIE_STATE_RUN && timeDelay > 1000)
		{
			SetState(ZOOMBIE_STATE_HIT);
			timeDelay = 0;
			if (isLeft)
				zoombiesword->SetLeft(true);
			else
				zoombiesword->SetLeft(false);
			zoombiesword->SetPosition(x, y);
			zoombiesword->SetEnable(true);
			zoombiesword->SetDead(false);
			zoombiesword->SetHP(1);
			
			for (UINT i = 0; i < coObjects->size(); i++)
			{
				if (dynamic_cast<CZoombieSword *>(coObjects->at(i)))
				{
					isCheck = true;
					break;
				}
			}
			if (!isCheck)
			{
				Grid *grid = Grid::GetInstance(0, 0, 0, 0);
				vector<LPGAMEOBJECT> ob;
				ob.push_back(this->zoombiesword);
				grid->Add(&ob);
			}

		
		}
		if (state == ZOOMBIE_STATE_HIT && timeDelay > 100)
		{
			SetState(ZOOMBIE_STATE_RUN);
			timeDelay = 0;
		}
	}
	zoombiesword->Update(dt, coObjects);
	LimitPos(limitX1, limitX2);
}

void CZoombie::Render()
{
}

void CZoombie::Render(ViewPort * viewport)
{
	int ani;
	int alpha = 255;
	if (untouchable)   alpha = 255;
	if (isEnable) {
		if (state == ZOOMBIE_STATE_RUN)
			ani = ZOOMBIE_ANI_RUN;
		else if (state == ZOOMBIE_STATE_HIT)
			ani = ZOOMBIE_ANI_HIT;
		animations[ani]->Render(viewport, x, y, alpha, isLeft);
	}

	
	CEnemy::Render(viewport);

}

void CZoombie::LimitPos(int limitX1, int limitY1)
{
	if (vx < 0 && x <= limitX1) {
		x = limitX1;
		isLeft = true;
	}

	if (vx > 0 && x >= limitX2) {
		x = limitX2;
		isLeft = false;
	}
}
