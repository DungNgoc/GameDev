#pragma once
#include "Enemy.h"
#include "TrooperSword.h"



class CTrooper:public CEnemy
{
	int untouchable;
	CTrooperSword *troopersword[2];
	DWORD timeDelay;
	bool isCheck;
public:
	CTrooper();
	~CTrooper();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	void Render(ViewPort * viewport);
	void LimitPos(int limitX1, int limitY1);
};






