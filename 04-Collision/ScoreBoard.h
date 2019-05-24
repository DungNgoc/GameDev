#pragma once
#include "ViewPort.h"
#include <string>
#include "Item.h"
#include <vector>
#include "Ninja.h"
#include "HP.h"
#include "BlackObject.h"


class ScoreBoard
{

private:
	ID3DXFont * font;
	RECT rect;
	Ninja *ninja;
	LPDIRECT3DDEVICE9 d3ddv;
	BlackObject *blackobject;
	wstring information;
	vector<HP*> *ninjaHPList;
	vector<HP*> *enemyHPList;
	vector<HP*> *noHPList;
	CSprite *sprite;
	LPD3DXSPRITE spriteHandler;
	
	Item* spiritpoints;
	Item* weapon;
	Item* throwingstar;
	Item* windmillstar;
	Item* flames;
	Item* firewheel;
	Item* jumpandslash;
	Item*it;
		
	int bossHP;
	int score;
	int time;
	int item;
	int energy;
	int life;
	int stage;
public:
	ScoreBoard();
	ScoreBoard(Ninja*ninja, int bossHP, LPDIRECT3DDEVICE9 d3ddv, LPD3DXSPRITE spriteHandler);
	~ScoreBoard();
	void Update(int bossHP, int time, int life, int stage);
	void Render(ViewPort *viewport);
};



