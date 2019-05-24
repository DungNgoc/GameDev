#include "ZoombieSword.h"
#include "Brick.h"
#include "Zoombie.h"
//#define SCREEN_WIDTH 320
CZoombieSword::CZoombieSword():CEnemy(1)
{

	isEnable = false;
	isDead = false;
	AddAnimation(15001);
	damage = 1;
	score = 0;
	vy = -0.2;
}

CZoombieSword::~CZoombieSword()
{
}

void CZoombieSword::ResetAnimation()
{
	resetAni(0);
}

void CZoombieSword::SetPosition(float x, float y)
{
	if (isLeft)
		x += 8;
	else x -= 8;
	CGameObject::SetPosition(x, y);
}

void CZoombieSword::Render()
{
	
}

void CZoombieSword::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = left + ZOOMBIE_SWORD_BBOX_WIDTH;
	top = y;
	bottom = top + ZOOMBIE_SWORD_BBOX_HEIGHT;
}

void CZoombieSword::Render(ViewPort * viewport)
{
	int ani = 0;
	int alpha = 255;
	if (isEnable)
		animations[ani]->Render(viewport, x, y, alpha, isLeft);
	D3DXVECTOR3 currentviewport = viewport->GetViewPortPosition();
	if (y < currentviewport.y || y > currentviewport.y + SCREEN_HEIGHT)
	{
		isEnable = false;
		//isDead = true;
		vy = -0.15;
	}
	
	CGameObject::Render(viewport);
}

int CZoombieSword::GetCurrentFrame()
{
	return 0;
}
void  CZoombieSword::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case 1:
		vy = -0.1;
		
		break;
	case 2:
		vy = 0.15;

	default:
		break;
	}
}

void CZoombieSword::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	/*if (isEnable == true)
		vy += 0.00500 * dt;
	
	if (isLeft)
	{
		vx = 0.2;
	}

	else {
		vx = -0.2;
	}
	CGameObject::Update(dt, coObjects);
	CEnemy::Update(dt);
	x += dx;
	y += dy;*/

	//CGameObject::Update(dt, coObjects);
	//CEnemy::Update(dt);
	////vy += 0.005*dt;
	//vx = 0.00003;
	//x += dx;

	//y += x * x - 1170 * x + 10;
	
	//y = 3 * x*x - 4 * x + 1;
	
	//for (UINT i = 0; i < coObjects->size(); i++)
	//{
	//	if (dynamic_cast<CBrick *>(coObjects->at(i)))
	//	{
	//	
	//		CBrick *brick = dynamic_cast<CBrick *>(coObjects->at(i));
	//		float l1, t1, r1, b1, l2, t2, r2, b2;
	//		GetBoundingBox(l1, t1, r1, b1);
	//		brick->GetBoundingBox(l2, t2, r2, b2);
	//		if (t1 <= b2 && b1 >= t2 && l1 <= r2 && r1 >= l2) {
	//			//vy = 0;
	//			//isEnable = false;
	//			SetState(2);
	//		}
	//	}
	//}
	///*time += dt;

	//if (time > 500)
	//{
	//	SetState(2);
	//	time -= 500;
	//}*/
	//vx = 0.1;
	//CGameObject::Update(dt);
	//x += dx;
	//y += dy





	if (isLeft)
		vx = 0.05;
	else
		vx = -0.05;

	CGameObject::Update(dt);
	x += dx;
	y += dy;

	if (isEnable == true)
		vy += 0.000400 * dt;
	
}
