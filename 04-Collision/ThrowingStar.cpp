#include "ThrowingStar.h"
#include "Enemy.h"
#include "Ninja.h"

CThrowingStar::CThrowingStar()
{
	this->AddAnimation(14001);
	useEnergy = 3;
	damage = 1;
}

CThrowingStar::~CThrowingStar()
{
}

void CThrowingStar::Update (DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CWeapon::Update(dt, coObjects);
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CEnemy *>(coObjects->at(i))) {

			CEnemy*enemy = dynamic_cast<CEnemy *>(coObjects->at(i));

			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			enemy->GetBoundingBox(l2, t2, r2, b2);

			if (t1 <= b2 && b1 >= t2 && l1 <= r2 && r1 >= l2) {
				if ((coObjects->at(i))->nx != 0)
				{
					if (enemy->isEnable != false) {
						enemy->SetHP(enemy->GetHP() - this->damage);
						Ninja::isThrowing = false;
						enemy->GetHitEffect()->SetEnable(true);
						isEnable = false;
					}
				}
			}

		}
	}
}

void CThrowingStar::Render(ViewPort *viewport)
{
	CWeapon::Render(viewport);
	//RenderBoundingBox(viewport);
}

void CThrowingStar::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	
	if (isLeft)
	{
		left = x;
		top = y;
		right = x + 8;
		bottom = y + 7;
	}
	else
	{
		left = x - 8;
		top = y;
		right = left + 8;
		bottom = y + 7;
	}
}

void CThrowingStar::SetPosition(float & x, float & y)
{
	CGameObject::SetPosition(x, y);
	x += NINJA_BBOX_WIDTH / 2;
}
