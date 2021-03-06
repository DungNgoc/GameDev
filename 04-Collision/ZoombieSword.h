#pragma once
#include "Enemy.h"
	

class CZoombieSword: public CEnemy
{
	CAnimation *ani;
	DWORD time;

public:
	CZoombieSword();
	~CZoombieSword();
	void ResetAnimation();
	void SetPosition(float x, float y);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render(ViewPort *viewport);
	int GetCurrentFrame();
	void SetState(int state);
	void resetAni(int ID) {
		animations[ID]->reset();
	}
	int GetDamage() {
		return damage;
	}
	void SetDamage(int damage) {
		this->damage = damage;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>*colliable_object = NULL);
};

