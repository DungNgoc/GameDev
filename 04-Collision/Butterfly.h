#pragma once
#include "Enemy.h"

class CButterfly : public CEnemy
{
public:
	CButterfly();
	
	//int untouchable;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	void Render(ViewPort * viewport);
	~CButterfly();
};

