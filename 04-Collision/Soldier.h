#pragma once
#pragma once
#include "Enemy.h"




class CSoldier : public CEnemy
{
	
	int untouchable;
	bool isLeft;

public:
	CSoldier();

	~CSoldier();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	void Render(ViewPort * viewport);
	void LimitPos(int limitX1, int limitY1);

};




