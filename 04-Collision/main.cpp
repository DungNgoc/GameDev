/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 04 - COLLISION

	This sample illustrates how to:

		1/ Implement SweptAABB algorithm between moving objects
		2/ Implement a simple (yet effective) collision frame work

	Key functions: 
		CGame::SweptAABB
		CGameObject::SweptAABBEx
		CGameObject::CalcPotentialCollisions
		CGameObject::FilterCollision

		CGameObject::GetBoundingBox
		
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "TileMap.h"
#include "Item.h"

#include "Ninja.h"
#include "ViewPort.h"
#include "Grid.h"

#include "Brick.h"
#include "Soldier.h"
#include "Panther.h"
#include "Butterfly.h"
#include "Eagle.h"

#include "main.h"


#include "LoadObject.h"
#include "ScoreBoard.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 120

#define ID_TEX_NINJA 0
#define ID_TEX_TILESET_31 1
#define ID_TEX_MISC 20
#define ID_TEX_SOLDIER 10

CGame *game;
Grid *grid;

Ninja *ninja;
LoadObject *loadobjects;
ViewPort *viewport;
TileMap *tilemap;
CSoldier *soldier;
CPanther *panther;
CButterfly *butterfly;
CEagle *eagle;
//DWORD time = 0;

int stage = 1;
ScoreBoard *scoreboard;
//HitEffect *hiteffect;
vector<LPGAMEOBJECT> listObjectsItem;
vector<LPITEM> listItem;
vector<LPGAMEOBJECT> coObjects;

class CSampleKeyHander: public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler; 

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_Z:
		if(!ninja->getJump())
			ninja->SetState(NINJA_STATE_JUMP);
		break;
	case DIK_A: // reset
		ninja->SetPosition(580, 50);
		break;
	}
	
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{

	if (ninja->GetState() == NINJA_STATE_DIE) return;
	if (game->IsKeyDown(DIK_1)) {
		ninja->SetPosition(0, 0);
		//ninja->SetMoveSinWave(false);
		ninja->SetMoveSquare(true);
	}
	else if (game->IsKeyDown(DIK_2))
	{
		ninja->SetPosition(0, 0);
		//ninja->SetMoveSquare(false);
		//ninja->SetMoveSinWave(true);
	}
	if (game->IsKeyDown(DIK_RIGHT)) {
		ninja->SetState(NINJA_STATE_WALKING_RIGHT);

	}
	else if (game->IsKeyDown(DIK_LEFT)) {
		ninja->SetState(NINJA_STATE_WALKING_LEFT);
	}
	else if (game->IsKeyDown(DIK_X) ){
		ninja->StartHitting();
		ninja->setHitting(true);
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{	
	
			ninja->SetState(NINJA_STATE_SIT);
	}
	else
		ninja->SetState(NINJA_STATE_IDLE);

	
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and ninja object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/

void LoadTextures(wstring file) {
	wifstream input;
	input.open(file, wistream::in);
	wstring checkEND;
	int id;
	wstring filepath;
	int colorR;
	int colorG;
	int colorB;
	while (input >> checkEND) {
		if (checkEND == L"END")
			return;
		else {
			id = stoi(checkEND.c_str());
			input >> filepath >> colorR >> colorG >> colorB;
			CTextures *texture = CTextures::GetInstance();
			LPCWSTR a = (LPCWSTR)filepath.c_str();
			texture->Add(id, a, D3DCOLOR_XRGB(colorR, colorG, colorB));
		}
	}
}
void LoadSprites(wstring file) {
	wifstream input;
	input.open(file, wistream::in);
	wstring checkEND;
	int id;
	int left, right, top, bottom, idtexture;
	while (input >> checkEND) {
		if (checkEND == L"END")
			return;
		else {
			id = stoi(checkEND.c_str());
			input >> left >> top >> right >> bottom >> idtexture;
			CTextures *texture = CTextures::GetInstance();
			CSprites *sprite = CSprites::GetInstance();
			sprite->Add(id, left, top, right, bottom, texture->Get(idtexture));
		}
	}
}
void LoadAnimations(wstring file) {
	wifstream input;
	input.open(file, wistream::in);
	wstring checkEND;
	int id;
	int frames, time;
	while (input >> checkEND) {
		if (checkEND == L"END")
			return;
		else {
			id = stoi(checkEND.c_str());
			input >> time >> frames;
			CAnimations *animation = CAnimations::GetInstance();
			LPANIMATION ani;
			ani = new CAnimation(time);
			int *x = new int[frames];
			for (int i = 0; i < frames; i++) {
				input >> x[i];
				ani->Add(x[i]);
			}
			animation->Add(id, ani);
		}
	}
}
void LoadResources(LPDIRECT3DDEVICE9 d3ddv, LPD3DXSPRITE sprite)
{
	CTextures * textures = CTextures::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	
	LPDIRECT3DTEXTURE9 texninja = textures->Get(ID_TEX_NINJA);
	sprites->Add(1, 0, 0, 1263, 15, textures->Get(ID_TEX_TILESET_31));

	LPDIRECT3DTEXTURE9 texSoldier = textures->Get(ID_TEX_SOLDIER);
	
	//hiteffect = new HitEffect();
	//hiteffect->SetEnable(true);
	//rites->Add(30004, 282, 51, 306, 92, texSoldier);
	LPANIMATION ani;
	
	ninja = new Ninja();
	
	
	

	tilemap = new TileMap(2048, 208, sprites->Get(1), 16, 16);
	tilemap->LoadListTileFromFile("Loadfile\\tileset31.txt");

	

	ninja->AddAnimation(1001);//walking right
	ninja->AddAnimation(1002);// idle right
	ninja->AddAnimation(1003);//hit right
	ninja->AddAnimation(1004);//spin right
	ninja->AddAnimation(1005);//idle sit
	ninja->AddAnimation(1006);//hit sit

	

	ninja->SetPosition(0, 50);
	

	loadobjects = new LoadObject();
	loadobjects->Load("Loadfile\\LoadObject.txt", &coObjects);
	

	for (int i = 0; i < 2; i++)
	{
		soldier = new CSoldier();
		soldier->AddAnimation(3001);
		soldier->AddAnimation(3002);
		soldier->SetPosition( 150 + i * 30, 127) ;
		//soldier->SetEnable(true);
		soldier->SetState(SOLDIER_STATE_WALKING);
		coObjects.push_back(soldier);
	}
	
	for (int i = 0; i < 1; i++)
	{
		panther = new CPanther();
		panther->AddAnimation(5001);
		//panther->AddAnimation(5002);
		panther->SetPosition(150 , 75);
		panther->SetState(PANTHER_STATE_WALKING);
		coObjects.push_back(panther);
	}
	
	butterfly = new CButterfly();
	butterfly->AddAnimation(7001);
	butterfly->SetPosition(180, 130);
	coObjects.push_back(butterfly);
	listObjectsItem.push_back(butterfly);
	
	Item *item = new Item(ITEM_SPIRIT_POINTS_BLU);
	item->SetEnable(false);
	//item->SetPosition(100, 100);
	listItem.push_back(item);

	/*for (int i = 0; i < 2; i++) {*/
	eagle = new CEagle();
	eagle->AddAnimation(8001);
	eagle->SetPosition(200, 45);
	coObjects.push_back(eagle);
	
	


	viewport = new ViewPort(0, 0);
	grid = new Grid(2048, 176, 256, 88);
	grid->Add(&coObjects);


	scoreboard = new ScoreBoard(ninja, 16, d3ddv, sprite);
}


void Update(DWORD dt)

{
	ninja->Update(dt, &coObjects);
	//time += dt;
	scoreboard->Update(16, 1000, ninja->GetLife(), 1);
	for (int i = 0; i < listObjectsItem.size(); i++)
	{
		listObjectsItem[i]->Update(dt, &coObjects);
		if (listObjectsItem[i]->GetDead())
		{
			listObjectsItem[i]->SetDead(false);
			listItem[i]->SetEnable(true);
			listItem[i]->SetPosition(listObjectsItem[i]->x, listObjectsItem[i]->y);
			coObjects.clear();
			coObjects.push_back(listItem[i]);
			grid->Add(&coObjects);
		}

	}
	grid->GetListOfObjects(&coObjects, viewport);
	for (int i = 0; i < listItem.size(); i++)
	{
		listItem[i]->Update(dt, &coObjects);
	}
	

	for (int i = 0; i < coObjects.size(); i++)
	{
		coObjects[i]->Update(dt,&coObjects);
	}
	if (ninja->x >= SCREEN_WIDTH / 2 - NINJA_BBOX_WIDTH / 2 && ninja->x <= 2048 - SCREEN_WIDTH / 2 - NINJA_BBOX_WIDTH / 2)
	{
		D3DXVECTOR3 currentViewPortPos = viewport->GetViewPortPosition();
		currentViewPortPos.x = ninja->x - SCREEN_WIDTH / 2 + NINJA_BBOX_WIDTH / 2;
		viewport->SetViewPortPosition(currentViewPortPos.x, currentViewPortPos.y);
	}

}

/*
	Render a frame 
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();


	
	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	
		/*D3DXMATRIX mt;
		D3DXMatrixScaling(&mt, -1.0, -1.0f, .0f);*/
		tilemap->Render(viewport);
		for (int i = 0; i < listItem.size(); i++)
		{
			listItem[i]->Render(viewport);
		}
		//listItem[0]->Render();
		scoreboard->Render(viewport);
		//listItem[0]->Render(viewport);
		ninja->Render(viewport);
		//hiteffect->Render(viewport);
		for (int i = 0; i < coObjects.size(); i++)
			coObjects[i]->Render(viewport);
		
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);

	LoadTextures(L"Loadfile\\LoadTexture.txt");
	LoadSprites(L"Loadfile\\LoadSprite.txt");
	LoadAnimations(L"Loadfile\\LoadAnimation.txt");
	LoadResources(game->d3ddv, game->spriteHandler);

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT*2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}