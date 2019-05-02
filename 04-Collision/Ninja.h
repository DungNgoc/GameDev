#pragma once
#include "GameObject.h"
#include "Sword.h"


#define NINJA_WALKING_RIGHT		0
#define NINJA_IDLE_RIGHT		1
#define NINJA_HIT_RIGHT         2
#define NINJA_ANI_JUMP			3
#define NINJA_SIT_RIGHT         4
#define NINJA_SIT_HIT			5


#define NINJA_STATE_HIT -5
#define NINJA_STATE_WALKING_RIGHT -4
#define NINJA_STATE_WALKING_LEFT -3
#define NINJA_STATE_DIE        -2
#define NINJA_STATE_IDLE      0
#define NINJA_STATE_JUMP      1
#define NINJA_STATE_SIT		  2


#define NINJA_WALKING_SPEED 0.1f

#define NINJA_BBOX_WIDTH  20

#define NINJA_GRAVITY 0.002f
#define NINJA_JUMP_SPEED_Y		0.5f

#define NINJA_HITTING_TIME 300

class Ninja: public CGameObject
{
	Sword *sword;
	int level;
	int untouchable;
	DWORD untouchable_start;
	int hitting;
	DWORD hitting_start;
	bool isMoveSquare;
	bool isMoveSinWave;
	bool isHitting;
	
	bool isJump;
	bool isTouchBrick;
	int flag;
	bool isLeft;
	int energy;
	int life;
	int numberofweapon;
	int hp;
	int currentWeapon;
public:
	Ninja() //: CGameObject()
	{
		untouchable = 0;
		sword = new Sword();
		life = 3;
		energy = 16;

	};
	bool get() {
		return isHitting;
	}
	
	void setHitting(bool isHitting) {
		this->isHitting = isHitting;
	}
	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render(ViewPort * viewport);
	virtual void Render();
	int GetScore();
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void SetMoveSquare(bool isMoveSquare) { this->isMoveSquare = isMoveSquare; }
	void SetMoveSinWave(bool isMoveSinWare) { this->isMoveSinWave = isMoveSinWare; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	bool getJump() { return isJump; }
	void StartHitting(){ hitting = 1; hitting_start = GetTickCount(); }
	void reset(int ID) {
		animations[ID]->reset();
	}
	int GetEnergy() { return this->energy; }
	int GetLife() { return life; }
	int SetHP(int hp) { this->hp = hp; }
	int GetHP() { return hp; }
	void SetTypeOfWeapon(int type);
	int GetTypeOfWeapon() { return currentWeapon; }
	//Ninja();
	//~Ninja();
};

