#pragma once
#include "GameObject.h"

#define NINJA_SET_POSITION_HIT_X 19
#define NINJA_SET_POSITION_HIT_Y 0
#define NINJA_SET_POSITION_SIT_X 19
#define NINJA_SET_POSITION_SIT_Y 7
class Sword:public CGameObject
{
public:
	Sword();
	void ResetAnimation();
	void SetPosition(float x, float y, bool Issit);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render(ViewPort *viewport);
	void resetAni(int ID) {
		animations[ID]->reset();
	}
	~Sword();//86 6 106 37  131 6 151 37
};

