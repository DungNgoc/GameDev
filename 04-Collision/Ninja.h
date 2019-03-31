#pragma once
#include "GameObject.h"

#define NINJA_WALKING_RIGHT		0
#define NINJA_IDLE_RIGHT		1
#define NINJA_IDLE_LEFT         2
#define NINJA_WALKING_LEFT      3
#define NINJA_HIT_RIGHT         4

#define NINJA_STATE_HIT -5
#define NINJA_STATE_WALKING_RIGHT -4
#define NINJA_STATE_WALKING_LEFT -3
#define NINJA_STATE_DIE        -2
#define NINJA_STATE_IDLE      0
#define NINJA_WALKING_SPEED 0.1f



#define NINJA_BBOX_WIDTH  20

#define NINJA_GRAVITY 0.002f

#define NINJA_HITTING_TIME 4000

class Ninja: public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	bool isMoveSquare;
	bool isMoveSinWave;
	bool isHitting;
public:
	Ninja() : CGameObject()
	{
		untouchable = 0;
	}
	bool get() {
		return isHitting;
	}
	void setHitting(bool isHitting) {
		this->isHitting = isHitting;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render(ViewPort * viewport);
	virtual void Render();
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void SetMoveSquare(bool isMoveSquare) { this->isMoveSquare = isMoveSquare; }
	void SetMoveSinWave(bool isMoveSinWare) { this->isMoveSinWave = isMoveSinWare; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void StartHitting(){ untouchable = 1; untouchable_start = GetTickCount(); }
	//Ninja();
	//~Ninja();
};

