#include "Sprites.h"
#include "Game.h"
#include "debug.h"


CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y, int alpha)
{
	CGame * game = CGame::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom, alpha);
}
void CSprite::Draw(ViewPort *viewport, float x, float y, int alpha)
{
	CGame * game = CGame::GetInstance();
	game->Draw(viewport, x, y, texture, left, top, right, bottom, alpha);
}


void CSprite::Draw(D3DXVECTOR3 &position, RECT &rect, int alpha)
{
	CGame * game = CGame::GetInstance();
	game->Draw(position, texture, rect, alpha);
}

void CSprite::Draw(ViewPort *viewport, float x, float y, int alpha, bool isLeft)
{
	CGame * game = CGame::GetInstance();
	game->Draw(viewport, x, y, texture, left, top, right, bottom, alpha, isLeft);
}
RECT CSprite::ReadCurrentSpritePosition()
{
	RECT rect;
	vector<int>* tempVector = this->spritePositions->at(this->index);

	// Giá trị đầu tiên là x, giá trị thứ 2 là y, giá trị thứ 3 là width, giá trị thứ 4 là height
	rect.left = tempVector->at(0);
	rect.top = tempVector->at(1);
	rect.right = rect.left + tempVector->at(2);
	rect.bottom = rect.top + tempVector->at(3);
	
	width = tempVector->at(2);
	height = tempVector->at(3);
	return rect;
}
void CSprite::Draw(D3DXVECTOR3 &position, bool flatright) {
	if (this->texture == NULL)
		return;
	float width = (float) (this->right - this->left);
	float height = (float)	(this->bottom - this->top);
	RECT rect = ReadCurrentSpritePosition();// read text
	D3DXVECTOR3  spriteCentre = D3DXVECTOR3(width, height, 0);

	D3DXMATRIX mt;
	float tempTurnRight = 1.0f;
	if (!flatright) {
		tempTurnRight = -1.0;
	}
	D3DXVECTOR3 scaling(tempTurnRight, 1.0f, -1.0f);
	D3DXMatrixTransformation(&mt, &D3DXVECTOR3(width / 2, height / 2, 0), NULL, &scaling, &spriteCentre, NULL, &position);
	
	CGame::GetInstance()->GetSpriteHandler()->SetTransform(&mt);
	CGame::GetInstance()->GetSpriteHandler()->Draw(this->texture, &rect, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}



void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t=this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1) 
	{
		currentFrame = 0; 
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}
		
	}

	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}
void CAnimation::Render(ViewPort *viewport, float x, float y, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}

	}
	 
	frames[currentFrame]->GetSprite()->Draw(viewport, x, y, alpha);
}
void CAnimation::Render(ViewPort *viewport, float x, float y, int alpha, bool isLeft)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}

	}

	frames[currentFrame]->GetSprite()->Draw(viewport, x, y, alpha, isLeft);
}


CAnimations * CAnimations::__instance = NULL;

CAnimations * CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	return animations[id];
}
void CSprite::Reset()
{
	this->index = 0;
}