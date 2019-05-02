#pragma once
#include "Sprites.h"
#include "GameObject.h"
class HP:public CGameObject
{
	int chose;
	CSprite *sprite;
public:
	void Render(ViewPort *viewport);
	void Render();
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Update(DWORD dt);
	HP(int chose);
	~HP();
};

