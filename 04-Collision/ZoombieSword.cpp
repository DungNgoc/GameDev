#include "ZoombieSword.h"



CZoombieSword::CZoombieSword()
{
	isLeft = false;
	AddAnimation(4001);

}

CZoombieSword::~CZoombieSword()
{
}

void CZoombieSword::ResetAnimation()
{
	resetAni(0);
}

void CZoombieSword::SetPosition(float x, float y, bool Issit)
{
	if (!isLeft)
	{
		/*x += ZOOMBIE_BBOX_WIDTH;
		y += SWORD_SET_POSITION_HIT_Y;*/
	}
	else {
		/*x -= SWORD_SET_POSITION_HIT_X;
		y += SWORD_SET_POSITION_HIT_Y;*/
	}
}

void CZoombieSword::Render()
{
}

void CZoombieSword::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}

void CZoombieSword::Render(ViewPort * viewport)
{
}

int CZoombieSword::GetCurrentFrame()
{
	return 0;
}

void CZoombieSword::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_object)
{
}
