#include "Weapon.h"
#include "Ninja.h"
#define SCREEN_WIDTH 320

CWeapon::CWeapon()
{
	isEnable = false;
}


CWeapon::~CWeapon()
{
}


void CWeapon::Update( DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isLeft)
		vx = 0.18;
	else
		vx = -0.18;
	
	CGameObject::Update(dt);
	x += dx;
	y += dy;
	//if (dynamic_cast<CThrowingStar *>(this)) {
	//	CThrowingStar *throwingstar = dynamic_cast<CThrowingStar *>(this);
	//	throwingstar->Update(dt, coObjects);
	//}
	
}

void CWeapon::ResetAnimation()
{
	resetAni(0);
	resetAni(1);
}

void CWeapon::SetPosition(float x, float y)
{
	CGameObject::SetPosition(x, y);
}

void CWeapon::Render(ViewPort * viewport)
{
	/*if (vx < 0)
		isLeft = false;
	else
	{
		isLeft = true;
	}*/
	//if(!isEnable)
	animations[0]->Render(viewport, x, y, 255, isLeft);
	D3DXVECTOR3 currentviewport = viewport->GetViewPortPosition();
	if (x < currentviewport.x || x>currentviewport.x + SCREEN_WIDTH)
	{
		isEnable = false;
	}
}

void CWeapon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}
