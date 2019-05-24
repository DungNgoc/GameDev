#pragma once
#include "Sprites.h"
#include "Textures.h"
#include "ViewPort.h"

class HitEffect
{
	int x, y;
	DWORD timeDelay;
	bool isEnable;
	vector<LPANIMATION>animation;
public:
	HitEffect();
	void Render(ViewPort *viewport);
	void Update(DWORD dt);
	void SetPosition(float x, float y) {
		this->x = x;
		this->y = y;
	} 
	void SetEnable(bool isEnable) {
		this->isEnable = isEnable;
	}
	void ResetAnimation();
	void resetAni(int ID) {
		animation[ID]->reset();
	}
	~HitEffect();
};

