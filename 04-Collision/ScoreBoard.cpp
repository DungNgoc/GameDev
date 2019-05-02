#include "ScoreBoard.h"
#include "Enemy.h"


ScoreBoard::ScoreBoard()
{
}


ScoreBoard::ScoreBoard(Ninja * ninja, int bossHP, LPDIRECT3DDEVICE9 d3ddv, LPD3DXSPRITE spriteHandler)
{
	this->bossHP = bossHP;
	this->ninja = ninja;
	this->d3ddv = d3ddv;
	this->spriteHandler = spriteHandler;
	/*BlackObject = new blackObject(SCREEN_WIDTH, 80);
	startkeyobject->SetPosition(0, 0);*/

	ninjaHPList = new std::vector<HP*>();
	for (int i = 0; i < 16; i++)
	{
		HP* ninjaHP = new HP(1);
		ninjaHP->SetPosition(120 + 7 * (i + 1), 12);
		ninjaHPList->push_back(ninjaHP);
	}
	enemyHPList = new std::vector<HP*>();
	for (int i = 0; i < 16; i++)
	{
		HP* enemyHP = new HP(1);
		enemyHP->SetPosition(160 + 7 * (i + 1), 23);
		enemyHPList->push_back(enemyHP);
	}
	noHPList = new vector<HP*>();
	for (int i = 0; i < 16; i++)
	{
		HP* noHP = new HP(2);
		noHP->SetPosition(120 + 7 * (i + 1), 12);
		noHPList->push_back(noHP);
	}

	spiritpoints = new Item(ITEM_SPIRIT_POINTS_BLU);
	spiritpoints->SetPosition(80, 43);

	throwingstar = new Item(ITEM_THROWING_STAR);
	throwingstar->SetPosition(335, 45);

	//windmillstar = new Item(ITEM_BLUE_WATER);
	//holyWater->SetPosition(335, 45);

	//boomerang = new Item(ITEM_BOOMERANG);
	//boomerang->SetPosition(335, 45);

	
	font = NULL;

	D3DXFONT_DESC FontDesc = {
		10,
		7,
		10,
		10,
		false,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY,
		FF_DONTCARE, L"font\\prstart.ttf" };


	D3DXCreateFontIndirect(d3ddv, &FontDesc, &font);

	SetRect(&rect, 0, 0, SCREEN_WIDTH *2, 85);
	information =  L"SCORE_000000 STAGE \n";
	information += L"TIME 0000    NINJA-                       \n";
	information += L"P-3		  ENEMY-                       \n";
}

ScoreBoard::~ScoreBoard()
{
}

void ScoreBoard::Update(int bossHP, int time, int life, int stage)
{

	this->time = time;
	this->stage = stage;
	this->bossHP = bossHP;

	wstring scoreString = to_wstring(ninja->GetScore());
	while (scoreString.length() < 6)
		scoreString = L"0" + scoreString;


	wstring timeString = to_wstring(this->time);
	while (timeString.length() < 4)
		timeString = L"0" + timeString;


	wstring stageString = to_wstring(this->stage);
	while (stageString.length() < 2)
		stageString = L"0" + stageString;


	information =  L"SCORE_" + scoreString  + L" STAGE " + stageString + L"\n";
	information += L"TIME " + timeString+ L"          PLAYER                        " + to_wstring(ninja->GetEnergy()) + L"\n";
	information += L"P-3.1 " + to_wstring(ninja->GetLife()) +L"                ENEMY                          "+ L"\n";


	switch (ninja->GetTypeOfWeapon())
	{
	case ITEM_THROWING_STAR:
		weapon = nullptr;
		weapon = throwingstar;
		break;
	case ITEM_WINDMILL_STAR:
		weapon = nullptr;
		weapon = windmillstar;
		break;
	case ITEM_FLAMES:
		weapon = nullptr;
		weapon = flames;
		break;
	/*case ITEM_ORG_FLO:
		weapon = nullptr;
		weapon = firewheel;
		break;
	case ITEM_BLUE_S:
		weapon = nullptr;
		weapon = jumpandslash;
		break;*/
	default:
		break;
	}
}

void ScoreBoard::Render(ViewPort * viewport)
{
	RECT newRect;
	//startkeyobject->Render();
	SetRect(&newRect, 0, 0, SCREEN_WIDTH, 100);
	font->DrawText(spriteHandler, information.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));

	/*for (int i = 0; i < noHPList->size(); i++)
	{
		noHPList->at(i)->Render();
	}*/
	int count = 0;
	for (int i = 0; i < ninjaHPList->size(); i++)
	{
		if (count < ninja->GetHP())
		{
			ninjaHPList->at(i)->Render();
		}
		count++;
	}
	count = 0;
	for (int i = 0; i<enemyHPList->size(); i++)
	{
		if (count < bossHP)
		{
			enemyHPList->at(i)->Render();
		}
		count++;
	}
	/*heart->Render();
	if (weapon != nullptr)
		weapon->Render();
	switch (simon->GetNumberOfWeapon()) {
	case 2: upgrade1->Render(); break;
	case 3: upgrade2->Render(); break;*/
	//}
}
