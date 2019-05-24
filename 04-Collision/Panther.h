#pragma once
#include "Enemy.h"

class CPanther : public CEnemy
{
	int untouchable;
	bool isLeft;
	

public:
	CPanther();
	~CPanther();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void LimitPos(int limitX1, int limitX2);
	virtual void Render();
	void Render(ViewPort * viewport);
	virtual void SetState(int state);
};

