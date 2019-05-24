#pragma once
#include "Enemy.h"



class CTrooperSword : public CEnemy
{
	CAnimation *ani;
public:
	CTrooperSword();
	~CTrooperSword();
	void ResetAnimation();
	void SetPosition(float x, float y);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render(ViewPort *viewport);
	int GetCurrentFrame();
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

