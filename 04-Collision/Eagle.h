#pragma once
#include "Enemy.h"
#define EAGLE_BBOX_WIDTH     15
#define EAGLE_BBOX_HEIGHT    15
	
#define EAGLE_ANI_RIGHT     0
#define EAGLE_ANI_1         2
#define EAGLE_ANI_2			1
#define EAGLE_FLY_SPEED   0.05f
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

