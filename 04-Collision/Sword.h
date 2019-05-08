#pragma once
#include "GameObject.h"

#define SWORD_SET_POSITION_HIT_X 21
#define SWORD_SET_POSITION_HIT_Y 4
#define SWORD_SET_POSITION_SIT_X 21
#define SWORD_SET_POSITION_SIT_Y 9

#define SWORD_ANI_HIT 0

#define SWORD_BBOX_HEIGHT 8
#define SWORD_BBOX_WIDTH  21

#define NINJA_BBOX_WIDTH 20
class Sword:public CGameObject
{
	int anirender;
	CAnimation *ani;
	int damage;

public:
	Sword();
	void ResetAnimation();
	void SetPosition(float x, float y, bool Issit);
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
	~Sword();//86 6 106 37  131 6 151 37
};

