#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "ViewPort.h"
#include "Sprites.h"
#include "HitEffect.h"

using namespace std;

#define ID_TEX_BBOX 100		// special texture to draw object bounding box

class CGameObject; 
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};



class CGameObject
{
public:

	float x;
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	float width;
	float height;
	int id;
	int nx;
	int ny;
	int type;
	int state;
	bool isLeft;

	bool isEnable;
	bool isDead;
	HitEffect *hitEffect;
	DWORD dt;
	ViewPort *viewport;
	vector<LPANIMATION> animations;
	int limitX1, limitX2;
public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	void SetWidth(float width) { this->width = width; }
	void SetHeight(float height) { this->height = height; }
	int GetWidth() {
		return width;
	}
	int GetHeight() {
		return height;
	}
	void SetLimitX(int limitX1, int limitX2) {
		this->limitX1 = limitX1;
		this->limitX2 = limitX2;
	}
	int GetState() { return this->state; }
	void SetId(int id) {
		this->id = id;
	}
	void SetType(int type) {
		this->type = type;
	}

	bool GetEnable() { return this->isEnable; }
	void SetEnable(bool isEnable) {
		this->isEnable = isEnable;
	}

	HitEffect *GetHitEffect() {
		return hitEffect;
	}
	void SetDead(bool isDead) {
		this->isDead = isDead;
	}
	bool GetDead() {
		return isDead;
	}
	void RenderBoundingBox();

	void RenderBoundingBox(ViewPort * viewport);

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);

	void AddAnimation(int aniId);

	CGameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(ViewPort *viewport);
	virtual void SetState(int state) { this->state = state; }


	~CGameObject();

};

