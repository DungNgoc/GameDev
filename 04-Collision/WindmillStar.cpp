#include "WindmillStar.h"
#include "Enemy.h"
#include "Ninja.h"

CWindmillStar::CWindmillStar()
{
	this->AddAnimation(13001);
	useEnergy = 5;
	damage = 1;
	nx = -1;
}


CWindmillStar::~CWindmillStar()
{
}
void CWindmillStar::CalculateNinjaPos( DWORD dt) {

	Ninja *ninja = Ninja::GetInstance();
	ninjaPos = D3DXVECTOR2(ninja->x, ninja->y);
	if (flytoboundingviewport == true)
	{
		distance = sqrt(
			pow(ninjaPos.x - x, 2) +
			pow(ninjaPos.y - y, 2));

		nx = (ninjaPos.x - x) / distance;
		ny = (ninjaPos.y - y) / distance;
	}
}
void CWindmillStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//CWeapon::Update(dt, coObjects);
	if (isLeft)
	{
		vx = 0.2;
		vy = 0.2;
	}
	else {
		vx = -0.2;
		vy = 0.2;
	}
	x += nx * vx * dt;
	y += ny * vy * dt;
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
						//isEnable = false;
					}
				}
			}

		}
	}

}

void CWindmillStar::Render(ViewPort * viewport)
{
	D3DXVECTOR2 currentvp = viewport->GetViewPortPosition();
	if (x <= viewport->GetViewPortPosition().x + 100 || x >= viewport->GetViewPortPosition().x + 320 - 100)
	{
		vx = -vx;
		flytoboundingviewport = true;
	}
	CWeapon::Render(viewport);
	//RenderBoundingBox(viewport);
}

void CWindmillStar::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (isLeft)
	{
		left = x;
		top = y;
		right = x + 16;
		bottom = y + 16;
	}
	else
	{
		left = x - 16;
		top = y;
		right = left + 16;
		bottom = y + 16;
	}
}

void CWindmillStar::SetPosition(float & x, float & y)
{
	CGameObject::SetPosition(x, y);
	x += NINJA_BBOX_WIDTH / 2;

}
