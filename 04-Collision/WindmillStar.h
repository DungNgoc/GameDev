#pragma once
#include "Weapon.h"
#define NINJA_BBOX_WIDTH 20
class CWindmillStar:public CWeapon
{
public:
	CWindmillStar();
	~CWindmillStar();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render(ViewPort *viewport);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetPosition(float &x, float &y);
};

