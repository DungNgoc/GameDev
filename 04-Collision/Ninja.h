#pragma once
#include "GameObject.h"
#include "Sword.h"
#include  "Weapon.h"
#include "ThrowingStar.h"
#include "WindmillStar.h"



class Ninja: public CGameObject
{
	Sword *sword;
	int level;
	int untouchable;
	DWORD untouchable_start;
	DWORD throw_start;

	int hitting;
	DWORD hitting_start;

	int hurtable;
	DWORD hurtable_start;

	bool isMoveSquare;
	bool isMoveSinWave;
	bool isHitting;
	bool isSit;
	
	bool isJump;
	bool isTouchBrick;
	bool isHurt;
	int flag;
	bool isLeft;
	int energy;
	int life;
	int numberofweapon;
	int hp;
	int damage;
	int ny;
	int currentWeapon;
	int ani;
	bool isUseWeapon;
public:
	static Ninja * __instance;
	CWeapon * weapons;
	CThrowingStar *throwingstar;
	CWindmillStar *windmillstar;
	Ninja(); //: CGameObject()
	static Ninja * GetInstance();
	bool GetUseWeapon() {
		return isUseWeapon;
	}
	bool get() {
		return isHitting;
	}
	
	void setHitting(bool isHitting) {
		this->isHitting = isHitting;
	}
	static bool isThrowing;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render(ViewPort * viewport);
	virtual void Render();
	static int GetScore();
	static void SetScore(int scrore);
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartHurting() { isHurt = true; hurtable = 1; hurtable_start = GetTickCount(); }

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
	void SetHP(int hp) { this->hp = hp; }
	int GetHP() { return hp; }
	bool GetHurt() { return isHurt; }
	void SetTypeOfWeapon(int type);
	int GetTypeOfWeapon() { return currentWeapon; }

	void StartThrowing();
	//Ninja();
	//~Ninja();
};

