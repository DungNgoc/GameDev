#pragma once
#include "Enemy.h"
#define PANTHER_BBOX_WIDTH     31 
#define PANTHER_BBOX_HEIGHT    15


#define PANTHER_STATE_WALKING   1 
#define PANTHER_ANI_WALKING     0

#define PANTHER_WALKING_SPEED   0.05f
class CPanther : public CEnemy
{
	int untouchable;
	bool isLeft;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void LimitPos(int limitX1, int limitX2);
	virtual void Render();
	void Render(ViewPort * viewport);

public:
	virtual void SetState(int state);
};

