#include "Trooper.h"
#include "Grid.h"

int i;
CTrooper::CTrooper():CEnemy(1)
{

	damage = 1;
	point = 200;
	for (i = 0; i < 1; i++) {
		troopersword[i] = new CTrooperSword();
		troopersword[i]->SetEnable(false);
	}
	//isCheck = true;
	
}


CTrooper::~CTrooper()
{
}

void CTrooper::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case TROOPER_STATE_HIT:
		vx = 0;
		break;
	case TROOPER_STATE_RUN:
		if (isLeft)
			vx = TROOPER_WALKING_SPEED;
		else 
			vx = -TROOPER_WALKING_SPEED;
	}
}

void CTrooper::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + TROOPER_BBOX_WIDTH;
	bottom = y + TROOPER_BBOX_HEIGHT;
}

void CTrooper::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CEnemy::Update(dt);
	x += dx;
	y += dy;
	if (isEnable && !isDead) {
		timeDelay += dt;
		
		if (state == TROOPER_STATE_RUN && timeDelay > 2000)
		{
			for (i = 0; i < 1; i++)
			{
				if (!troopersword[i]->GetEnable())// && state == TROOPER_STATE_RUN && timeDelay > 2000)
				{
					SetState(TROOPER_STATE_HIT);
					timeDelay = 0;
					if (isLeft)
						troopersword[i]->SetLeft(true);
					else
						troopersword[i]->SetLeft(false);

					troopersword[i]->SetPosition(x + i * 15, y);
					troopersword[i]->SetEnable(true);

					for (UINT i = 0; i < coObjects->size(); i++)
					{
						if (dynamic_cast<CTrooperSword *>(coObjects->at(i)))
						{
							isCheck = true;
							break;
						}
					}
					if (!isCheck)
					{
						Grid *grid = Grid::GetInstance(0, 0, 0, 0);
						vector<LPGAMEOBJECT> ob;
						ob.push_back(troopersword[i]);
						grid->Add(&ob);
					}
				}
				

			}

		}
		
			
		if (state == TROOPER_STATE_HIT && timeDelay > 1000)
			{
				SetState(TROOPER_STATE_RUN);
				timeDelay = 0;
		}
		
	}
//	if (troopersword->GetEnable())
	for(i =0;i<1;i++)
		troopersword[i]->Update(dt, coObjects);
	LimitPos(limitX1, limitX2);

}

void CTrooper::Render()
{
	
}

void CTrooper::Render(ViewPort * viewport)
{
	int ani;
	int alpha = 255;
	if (untouchable)   alpha = 255;
	if (isEnable) {
		if (state == TROOPER_STATE_RUN)
			ani = TROOPER_ANI_RUN;
		else if(state == TROOPER_STATE_HIT)
			ani = TROOPER_ANI_HIT;
		animations[ani]->Render(viewport, x, y, alpha, isLeft);
	}
	

	CEnemy::Render(viewport);
}

void CTrooper::LimitPos(int limitX1, int limitY1)
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
