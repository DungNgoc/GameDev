#pragma once
#include "Weapon.h"
#define NINJA_BBOX_WIDTH 20
#define SCREEN_WIDTH 320
class CWindmillStar:public CWeapon
{
	D3DXVECTOR2 ninjaPos;
	float distance;
	bool flytoboundingviewport;
public:
	CWindmillStar();
	~CWindmillStar();
	void CalculateNinjaPos( DWORD dt);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render(ViewPort *viewport);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetPosition(float &x, float &y);
};

