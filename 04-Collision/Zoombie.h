#pragma once
#include "Enemy.h"
#include "ZoombieSword.h"


#define ZOOMBIE_WALKING_SPEED 0.04f
#define ZOOMBIE_GRAVITY 0.002f
	
#define ZOOMBIE_BBOX_WIDTH 16
#define ZOOMBIE_BBOX_HEIGHT 32
#define ZOOMBIE_BBOX_HEIGHT_DIE 9
		
#define ZOOMBIE_STATE_HIT 100
#define ZOOMBIE_STATE_RUN 200
	
#define ZOOMBIE_ANI_WALKING 0

class CZoombie : public CEnemy
{
	CZoombieSword *zoombiesword;
	int untouchable;
	bool isLeft;
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

