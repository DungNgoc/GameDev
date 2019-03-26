#pragma once
#include <d3dx9.h>

class ViewPort
{
public:
	D3DXVECTOR3 viewPortPos;
public:
	ViewPort(float x, float y);
	ViewPort();
	~ViewPort();
	D3DXVECTOR3 SetPositionInViewPort(D3DXVECTOR3 position);
	void SetViewPortPosition(float x, float y);
	D3DXVECTOR3 GetViewPortPosition();
};

