#pragma once
#pragma once
#include "Enemy.h"


#define SOLDIER_WALKING_SPEED 0.05f
#define SOLDIER_GRAVITY 0.002f

#define SOLDIER_BBOX_WIDTH 24
#define SOLDIER_BBOX_HEIGHT 32
#define SOLDIER_BBOX_HEIGHT_DIE 9

#define SOLDIER_STATE_WALKING 100
#define SOLDIER_STATE_DIE 200

#define SOLDIER_ANI_WALKING 0
#define SOLDIER_ANI_DIE 1

class CSoldier : public CEnemy
{
	int untouchable;
	bool isLeft;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	void Render(ViewPort * viewport);
	
public:
	virtual void SetState(int state);
};




