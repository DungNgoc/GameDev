#include "HitEffect.h"




HitEffect::HitEffect()
{
	animation.push_back(CAnimations::GetInstance()->Get(ID_ANI_EFFECT));
	timeDelay = 0;
	isEnable = false;
}

void HitEffect::Render(ViewPort * viewport)
{
	if (isEnable)
		animation[0]->Render(viewport, x, y);
}

void HitEffect::Update(DWORD dt)
{
	if (isEnable) {
		timeDelay += dt;
		if (timeDelay > 450) {
			timeDelay = 0;
			isEnable = false;
		}
	}
}


HitEffect::~HitEffect()
{
}
