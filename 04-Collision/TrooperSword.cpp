#include "TrooperSword.h"
#include "Trooper.h"
#include "Brick.h"

CTrooperSword::CTrooperSword():CEnemy(1)
{
	isEnable = false;
	isDead = false;
	AddAnimation(17001);
	damage = 1;
	score = 0;
	
}


CTrooperSword::~CTrooperSword()
{
}

void CTrooperSword::ResetAnimation()
{
	resetAni(0);
}

void CTrooperSword::SetPosition(float x, float y)
{
	if (isLeft)
	x += TROOPER_BBOX_WIDTH;
	else x -= TROOPER_BBOX_WIDTH;
	y += 9;
	
	CGameObject::SetPosition(x, y);
}

void CTrooperSword::Render()
{
}

void CTrooperSword::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = left + TROOPER_SWORD_BBOX_WIDTH;
	top = y;
	bottom = top + TROOPER_SWORD_BBOX_HEIGHT;
}

void CTrooperSword::Render(ViewPort * viewport)
{
	int ani = 0;
	int alpha = 255;
	if(isEnable)
	animations[ani]->Render(viewport, x, y, alpha, isLeft);
	D3DXVECTOR3 currentviewport = viewport->GetViewPortPosition();
	if (x < currentviewport.x || x>currentviewport.x + SCREEN_WIDTH)
	{
		isEnable = false;
		//isDead = true;
	}
	//RenderBoundingBox(viewport);
	CGameObject::Render(viewport);
}

int CTrooperSword::GetCurrentFrame()
{
	return 0;
}

void CTrooperSword::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	CGameObject::Update(dt, coObjects);
	CEnemy::Update(dt);
	x += dx;
	y += dy;
	
		if (isLeft)
			vx = 0.05;
		else vx =- 0.05;
	
}
