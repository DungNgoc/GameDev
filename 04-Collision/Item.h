#pragma once
#include "GameObject.h"
#include "Ninja.h"
#include <time.h>



#define ITEM_SMALL_DARTS 9013
#define ITEM_BIG_DARTS	 9014
#define ITEM_FIRE        9015
#define ITEM_SMALL_BREAK 9016
#define ITEM_BIG_BREAK	 9017




class Item;
typedef Item * LPITEM;

class Item : public CGameObject
{
	static Ninja *ninja;
	CSprite *sprite;
	int itemType;
	CAnimation *anirender;
	bool isTouchBrick;
	Item *it;
public:
	Item();
	Item(int itemType);
	~Item();
	void SetState(int state);
	static void TakeSimonPointer(Ninja *ninja);
	void Render(ViewPort *viewport);
	int GetCurrentFrame();
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Random();
	void RandomItem();
	void RandomWeapon();
	int GetItemType() { return itemType; }
};

