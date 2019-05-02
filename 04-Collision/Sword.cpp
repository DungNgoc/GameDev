#include "Sword.h"
#include "Enemy.h"



Sword::Sword()
{
	isLeft = true;
	AddAnimation(4001);

}
void Sword::ResetAnimation()
{
	resetAni(0);
	/*resetAni(1);
	resetAni(2);*/
	
}


void Sword::SetPosition(float x, float y, bool Issit)
{

	if (Issit == false)
	{
		if (!isLeft)
		{
			x += NINJA_BBOX_WIDTH;
			y += SWORD_SET_POSITION_HIT_Y;
		}		 
		else	{
			x -= SWORD_SET_POSITION_HIT_X;
			y += SWORD_SET_POSITION_HIT_Y;
		}
		
	}
	else
	{
		if (!isLeft)
		{
			x -= SWORD_SET_POSITION_SIT_X;
			y += SWORD_SET_POSITION_SIT_Y;
		}		
		else	 {
			x += SWORD_SET_POSITION_SIT_X;
			y += SWORD_SET_POSITION_SIT_Y;
		}
	}
	
	//else
	//	x -= MORNINGSTAR_SET_POSITION_X;
	CGameObject::SetPosition(x, y);
}
void Sword::Render()
{
}

void Sword::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	
	top = y;
	bottom = y + SWORD_BBOX_HEIGHT;
	if (isLeft)
	{	
		left = x;
		right = left + SWORD_BBOX_WIDTH;
	}
	else
	{
		left = x;
		right = x + SWORD_BBOX_WIDTH;
	}
}


void Sword::Render(ViewPort * viewport)
{
	int ani=0;
	int alpha = 255;
	animations[ani]->Render(viewport, x, y, alpha, isLeft);
	RenderBoundingBox(viewport);
}
int Sword::GetCurrentFrame() {
	if (anirender == SWORD_ANI_HIT)
		ani = animations[SWORD_ANI_HIT];
	return ani->getCurrentFrame();
}
		

void Sword::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_object)
{
	CGameObject::Update(dt);
	for (UINT i = 0; i < colliable_object->size(); i++)
	{
		if (dynamic_cast<CEnemy*>(colliable_object->at(i)))
		{
			CEnemy *enemy = dynamic_cast<CEnemy*>(colliable_object->at(i));
			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			enemy->GetBoundingBox(l2, t2, r2, b2);
			if(!enemy->GetDead())
			if (t1 <= b2 && b1 >= t2 && l1 <= r2 && r1 >= l2) {
				if ((colliable_object->at(i))->nx != 0) {
					enemy->GetHitEffect()->SetEnable(true);
					if (enemy->GetEnable()) {
						enemy->SetEnable(false);
						enemy->SetDead(true);
					}
				}
			}
		}
	}
}

Sword::~Sword()
{
}
