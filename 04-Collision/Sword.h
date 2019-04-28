#pragma once
#include "GameObject.h"

#define SWORD_SET_POSITION_HIT_X 19
#define SWORD_SET_POSITION_HIT_Y 0
#define SWORD_SET_POSITION_SIT_X 19
#define SWORD_SET_POSITION_SIT_Y 7

#define SWORD_ANI_HIT 0

#define SWORD_BBOX_HEIGHT 8
#define SWORD_BBOX_WIDTH  17
class Sword:public CGameObject
{
	int anirender;
	CAnimation *ani;

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
	void Update(DWORD dt, vector<LPGAMEOBJECT>*colliable_object = NULL);
	~Sword();//86 6 106 37  131 6 151 37
};

