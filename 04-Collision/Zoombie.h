#pragma once
#include "Enemy.h"
#include "ZoombieSword.h"



class CZoombie : public CEnemy
{
	CZoombieSword *zoombiesword;
	int untouchable;
	bool isLeft;
	DWORD timeDelay;
	bool isCheck;
public:
	CZoombie();
	~CZoombie();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	void Render(ViewPort * viewport);
	void LimitPos(int limitX1, int limitY1);
};

