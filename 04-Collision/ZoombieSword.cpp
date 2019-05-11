#include "ZoombieSword.h"
#include "Brick.h"
#include "Zoombie.h"

CZoombieSword::CZoombieSword()
{
	isLeft = false;
	AddAnimation(15001);
	//isEnable = true;
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
	x+=8;
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
	animations[ani]->Render(viewport, x, y, alpha, isLeft);
	//RenderBoundingBox(viewport);
}

int CZoombieSword::GetCurrentFrame()
{
	return 0;
}

void CZoombieSword::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//CGameObject::Update(dt);
	/*if (!isLeft)
		vx = 0.4;
	else
		vx = -0.4;*/
	vx = -0.2;
	CGameObject::Update(dt, coObjects);
	x += dx;
	y += dy;
	if (isEnable == true)
		vy += 0.000900 * dt;
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CBrick *>(coObjects->at(i)))
		{
			CBrick *brick = dynamic_cast<CBrick *>(coObjects->at(i));
			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			brick->GetBoundingBox(l2, t2, r2, b2);
			if (t1 <= b2 && b1 >= t2 && l1 <= r2 && r1 >= l2) {
				vy = -0.4;
				isEnable = false;
			}
		}
	}


}
