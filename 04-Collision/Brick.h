#pragma once
#include "GameObject.h"



class CBrick : public CGameObject
{

public:
	CBrick();
	~CBrick();
	virtual void Render(ViewPort *viewport);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

};


