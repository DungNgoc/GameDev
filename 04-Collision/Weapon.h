#pragma once
#include "GameObject.h"

class CWeapon:public CGameObject
{
protected:
	int useEnergy;
	int damage;
	int count;
public:
	CWeapon();
	~CWeapon();
	void resetAni(int aniID) { animations[aniID]->reset(); }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void ResetAnimation();
	virtual void SetPosition(float x, float y);
	virtual void Render(ViewPort *camera);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	int GetUseEnergy() { return useEnergy; }
	int GetDamage() { return damage; }
	void SetDamage(int damage) { this->damage = damage; }
};

