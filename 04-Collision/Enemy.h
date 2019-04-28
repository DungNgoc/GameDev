#pragma once
#include "GameObject.h"
class CEnemy : public CGameObject
{
public:
	CEnemy();
	~CEnemy();
	 void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	 void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	 void Render() = 0;
	 void Render(ViewPort *viewport) = 0;
	 void SetState(int state) { this->state = state; }

};

