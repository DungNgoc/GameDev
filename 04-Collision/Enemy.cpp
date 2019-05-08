#include "Enemy.h"
int CEnemy::score = 0;
float CEnemy::stopTime = 0;
int CEnemy::timestop = 0;
DWORD CEnemy::timestop_start = 0;
bool CEnemy::IsStop = false;

void CEnemy::AddScore()
{
	CEnemy::score += point;
}
void CEnemy::SetScore(int score)
{
	CEnemy::score += score;
}

CEnemy::CEnemy()
{
}


CEnemy::~CEnemy()
{
}


void CEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!IsStop)
		CGameObject::Update(dt, coObjects);
	if (!isDead)
	{
		if (isEnable == true)
		{
			if (hp <= 0)
			{
				isDead = true;
				isEnable = false;
				AddScore();
				return;
			}
		
			
		}

	}
	
}
int CEnemy::GetScore()
{
	return score;
}

void CEnemy::Render(ViewPort * viewport)
{
	CGameObject::Render(viewport);
}
