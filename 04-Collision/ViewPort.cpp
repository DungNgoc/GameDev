#include "ViewPort.h"



ViewPort::ViewPort()
{
}


ViewPort::ViewPort(float x, float y)
{
	viewPortPos.x = x;
	viewPortPos.y = y;
	viewPortPos.z = 0;
}

ViewPort::~ViewPort()
{
}

D3DXVECTOR3 ViewPort::SetPositionInViewPort(D3DXVECTOR3 position)
{
	D3DXVECTOR3 pos;
	pos.x = position.x-viewPortPos.x;
	pos.y = position.y-viewPortPos.y;
	pos.z = 0;
	return D3DXVECTOR3(pos.x, pos.y, pos.z);
}

void ViewPort::SetViewPortPosition(float x, float y)
{
	viewPortPos.x = x;
	viewPortPos.y = y;
	viewPortPos.z = 0;
}

D3DXVECTOR3 ViewPort::GetViewPortPosition()
{
	return viewPortPos;
}
