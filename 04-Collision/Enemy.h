#pragma once
#include "GameObject.h"
class Enemy;
typedef Enemy * LPENEMY;
class CEnemy : public CGameObject
{
protected:
	int hp;
	int e_prevHP;
	int hpC;
	int damage;
	int point;
	bool isGrounded;
	static int score;
	bool isLeft;
public:
	static int timestop;
	static DWORD timestop_start;
	static float stopTime;
	static bool IsStop;
	CEnemy();
	CEnemy(int hp)
	{
		this->hp = hp;
		
	};
	~CEnemy();
	static void StartTimeStop() { timestop = 1; timestop_start = GetTickCount(); };
	 void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	 void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	 static int GetScore();
	 void AddScore();
	 static void SetScore(int score);
	 void Render(ViewPort *viewport);
	 void SetState(int state) { this->state = state; }
	 void SetDamage(int damage) {
		 this->damage = damage;
	 }
	 int GetDamage() {
		 return damage;
	 }
	 void SetHP(int hp) {
		 this->hp = hp;
	 }
	 int GetHP() {
		 return hp;
	 }
	 void SetLeft(int isLeft) {
		 this->isLeft = isLeft;
	 }

};

