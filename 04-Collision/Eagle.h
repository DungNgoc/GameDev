#pragma once
#include "Enemy.h"

class CEagle: public CEnemy
{
	//bool isLeft;
	int anirender;
	CAnimation *ani;
	int damage;
public:
	CEagle();
	
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void LimitPos(int limitX1, int limitX2);
	virtual void Render();
	void Render(ViewPort * viewport);
	
	~CEagle();
};

