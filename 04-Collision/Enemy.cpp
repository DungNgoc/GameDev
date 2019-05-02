#include "Enemy.h"
int CEnemy::score = 0;


void CEnemy::AddScore()
{
}

CEnemy::CEnemy()
{
}


CEnemy::~CEnemy()
{
}


void CEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{/*
	if (!isDead) {
		if (isEnable) {

		}
	}*/
	if (isDead)
		isEnable = true;
}
int CEnemy::GetScore()
{
	return score;
}

void CEnemy::Render(ViewPort * viewport)
{
	CGameObject::Render(viewport);
}
