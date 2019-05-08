#pragma once
#include "Enemy.h"
#define BUTTERFLY_BBOX_WIDTH     15
#define BUTTERFLY_BBOX_HEIGHT    15
		
#define BUTTERFLY_ANI_RIGHT     0
	
#define BUTTERFLY_WALKING_SPEED   0
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

