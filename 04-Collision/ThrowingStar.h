#pragma once
#include "Weapon.h"

class CThrowingStar: public CWeapon
{
public:
	CThrowingStar();
	~CThrowingStar();
	void Update( DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render(ViewPort *viewport);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetPosition(float &x, float &y);
};

