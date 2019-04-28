#pragma once
#include "GameObject.h"
#define EAGLE_BBOX_WIDTH     15
#define EAGLE_BBOX_HEIGHT    15
	
#define EAGLE_ANI_RIGHT     0
	
#define EAGLE_FLY_SPEED   0.05f
class CEagle: public CGameObject
{
public:
	CEagle();
	
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	void Render(ViewPort * viewport);
	~CEagle();
};

