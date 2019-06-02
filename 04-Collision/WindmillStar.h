#pragma once
#include "Weapon.h"
#define NINJA_BBOX_WIDTH 20
#define SCREEN_WIDTH 320
class CWindmillStar:public CWeapon
{
	D3DXVECTOR2 ninjaPos;
	float distance;
	bool flytoboundingviewport;
	float ny;
	float nx;
public:
	CWindmillStar();
	~CWindmillStar();
	void CalculateNinjaPos( DWORD dt);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render(ViewPort *viewport);
	bool getFlytoboudingviewport() {
		return flytoboundingviewport;
	}
	void setFlytoboudingviewport(bool flytoboundingviewport) {
		this->flytoboundingviewport= flytoboundingviewport;
	}
	void Setnx(float nx)
	{
		this->nx = nx;
	}
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetPosition(float x, float y);
};

