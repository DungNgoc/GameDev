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
	void AddScore();
public:
	CEnemy();
	~CEnemy();
	 void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	 void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	 static int GetScore();
	 void Render() = 0;
	 void Render(ViewPort *viewport);
	 void SetState(int state) { this->state = state; }

};

