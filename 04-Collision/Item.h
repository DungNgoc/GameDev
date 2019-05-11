#pragma once
#include "GameObject.h"
#include "Ninja.h"
#include <time.h>

#define ITEM_SPIRIT_POINTS_BLU   90001
#define ITEM_SPIRIT_POINTS_RED   90002

#define ITEM_BONUS_POINTS_BLUE	 90009
#define ITEM_BONUS_POINT_RED	 90010
#define ITEM_HEALTH_BLU          90011
#define ITEM_HEALTH_RED          90012
#define ITEM_TIME_FREEZE	     90018
#define ITEM_EXTRA_LIFE        	 90008



#define ITEM_THROWING_STAR       90003
#define ITEM_WINDMILL_STAR       90004
#define ITEM_JUMP_AND_SLASH  	 90005
#define ITEM_FLAMES	             90006
#define ITEM_FIRE_WHEEL     	 90007



#define ITEM_SMALL_DARTS 9013
#define ITEM_BIG_DARTS	 9014
#define ITEM_FIRE        9015
#define ITEM_SMALL_BREAK 9016
#define ITEM_BIG_BREAK	 9017

#define ITEM_ENERGY  90019


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

