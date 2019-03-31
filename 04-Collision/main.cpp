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

#include "Ninja.h"
#include "ViewPort.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 270

#define MAX_FRAME_RATE 120

#define ID_TEX_NINJA 0
#define ID_TEX_TILESET_31 1



CGame *game;

Ninja *ninja;
ViewPort *viewport;
TileMap *tilemap;

vector<LPGAMEOBJECT> objects;

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
	/*case DIK_X:
		ninja->SetState(NINJA_STATE_HIT);
		break;*/
		//case DIK_A: // reset
		//	ninja->SetState(ninja_STATE_IDLE);
		//	ninja->SetPosition(50.0f,0.0f);
		//	ninja->SetSpeed(0, 0);
		//	break;
		//}
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	// disable control key when ninja die 
	/*if (ninja->GetState() == ninja_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
		ninja->SetState(ninja_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		ninja->SetState(ninja_STATE_WALKING_LEFT);
	else
		ninja->SetState(ninja_STATE_IDLE);*/

	if (ninja->GetState() == NINJA_STATE_DIE) return;
	if (game->IsKeyDown(DIK_1)) {
		ninja->SetPosition(0, 0);
		ninja->SetMoveSinWave(false);
		ninja->SetMoveSquare(true);
	}
	else if (game->IsKeyDown(DIK_2))
	{
		ninja->SetPosition(0, 0);
		ninja->SetMoveSquare(false);
		ninja->SetMoveSinWave(true);
	}
	if (game->IsKeyDown(DIK_RIGHT)) {
		ninja->SetState(NINJA_STATE_WALKING_RIGHT);

	}
	else if (game->IsKeyDown(DIK_LEFT)) {
		ninja->SetState(NINJA_STATE_WALKING_LEFT);
	}
	else if (game->IsKeyDown(DIK_X) ){
		//ninja->SetState(NINJA_STATE_HIT);
		ninja->setHitting(true);
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
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_NINJA, L"textures\\ninja.png",D3DCOLOR_XRGB(255, 163, 177));
	textures->Add(ID_TEX_TILESET_31, L"textures\\tileset31.png", D3DCOLOR_XRGB(255, 163, 177));
	
	/*textures->Add(ID_TEX_MISC, L"textures\\misc.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_ENEMY, L"textures\\enemies.png", D3DCOLOR_XRGB(3, 26, 110));


	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(250, 250, 250));*/


	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	
	LPDIRECT3DTEXTURE9 texninja = textures->Get(ID_TEX_NINJA);
	sprites->Add(1, 0, 0, 1263, 15, textures->Get(ID_TEX_TILESET_31));
	 

	sprites->Add(10001, 339, 5, 359, 37, texninja); //walk right
	sprites->Add(10002, 368, 5, 390, 37, texninja);
	sprites->Add(10003, 400, 5, 420, 37, texninja);

	sprites->Add(10004, 3, 5, 20, 37, texninja);//idle right
	
	
	sprites->Add(10005, 506, 6, 526, 37, texninja); 
	sprites->Add(10006, 475, 6, 498, 37, texninja);//walk left
	sprites->Add(10007, 445, 6, 465, 37, texninja);


	sprites->Add(10008, 845, 5, 862, 37, texninja);//idle left

	sprites->Add(10009, 42, 6, 60, 37, texninja);//hit standing right
	sprites->Add(10010, 66, 6, 106, 37, texninja);
	sprites->Add(10011, 111, 6, 140, 37, texninja);

	sprites->Add(10012, 805, 6, 824, 37, texninja);//hit standing left
	sprites->Add(10013, 709, 8, 799, 37, texninja);
	sprites->Add(10014, 725, 8, 754, 37, texninja);

	sprites->Add(10015, 35, 53, 53, 76, texninja);//hit sitting right
	sprites->Add(10016, 58, 53, 97, 76, texninja);
	sprites->Add(10017, 100, 53, 129, 76, texninja);

	sprites->Add(10018, 812, 53, 830, 76, texninja);//hit sitting left
	sprites->Add(10019, 768, 53, 807, 76, texninja);
	sprites->Add(10020, 736, 52, 765, 76, texninja);

	sprites->Add(10021, 142, 53, 158, 75, texninja);// spin right
	sprites->Add(10022, 166, 55, 188, 71, texninja);
	sprites->Add(10023, 194, 53, 209, 75, texninja);
	sprites->Add(10024, 217, 55, 239, 71, texninja);

	sprites->Add(10025, 707, 53, 723, 75, texninja);//spin left
	sprites->Add(10026, 677, 55, 699, 71, texninja);
	sprites->Add(10027, 655, 53, 671, 75, texninja);
	sprites->Add(10028, 626, 55, 648, 71, texninja);

	sprites->Add(10029, 263, 50, 287, 75, texninja);//spin hitting right
	sprites->Add(10030, 294, 51, 319, 75, texninja);
	sprites->Add(10031, 327, 51, 351, 76, texninja);
	sprites->Add(10032, 358, 51, 383, 75, texninja);

	sprites->Add(10033, 578, 50, 602, 75, texninja);//spin hitting left
	sprites->Add(10034, 546, 51, 571, 75, texninja);
	sprites->Add(10035, 514, 51, 538, 76, texninja);
	sprites->Add(10036, 482, 51, 507, 75, texninja);


	LPANIMATION ani;
	ani = new CAnimation(100);	//  walk right
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(1001, ani);
	ninja = new Ninja();
	

	

	tilemap = new TileMap(2048, 208, sprites->Get(1), 16, 16);
	tilemap->LoadListTileFromFile("Loadfile\\tileset31.txt");


	ani = new CAnimation(100);
	ani->Add(10004);
	animations->Add(1002, ani);

	ani = new CAnimation(100);
	ani->Add(10008);
	animations->Add(1003, ani);
	

	ani = new CAnimation(100);
	ani->Add(10005);
	ani->Add(10006);
	ani->Add(10007);
	animations->Add(1004, ani);
	
	ani = new CAnimation(100);
	ani->Add(10009);
	ani->Add(10010);
	ani->Add(10011);
	animations->Add(1005, ani);

	ani = new CAnimation(100);
	ani->Add(10012);
	ani->Add(10013);
	ani->Add(10014);
	animations->Add(1006, ani);
	

	ninja->AddAnimation(1001);//walking right
	ninja->AddAnimation(1002);// idle right
	ninja->AddAnimation(1003);// idle left
	ninja->AddAnimation(1004);// walking left
	ninja->AddAnimation(1005);//hit right
	ninja->AddAnimation(1006);//hit left


	ninja->SetPosition(0, 100);
	//sprites->Add(10011, 186, 154, 200, 181, texninja);		// idle left
	//sprites->Add(10012, 155, 154, 170, 181, texninja);		// walk
	//sprites->Add(10013, 125, 154, 140, 181, texninja);

	//sprites->Add(10099, 215, 120, 231, 135, texninja);		// die 

	//// small
	//sprites->Add(10021, 247, 0, 259, 15, texninja);			// idle small right
	//sprites->Add(10022, 275, 0, 291, 15, texninja);			// walk 
	//sprites->Add(10023, 306, 0, 320, 15, texninja);			// 

	//sprites->Add(10031, 187, 0, 198, 15, texninja);			// idle small left

	//sprites->Add(10032, 155, 0, 170, 15, texninja);			// walk
	//sprites->Add(10033, 125, 0, 139, 15, texninja);			// 


	//LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	//sprites->Add(20001, 408, 225, 424, 241, texMisc);

	//LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_ENEMY);
	//sprites->Add(30001, 5, 14, 21, 29, texEnemy);
	//sprites->Add(30002, 25, 14, 41, 29, texEnemy);

	//sprites->Add(30003, 45, 21, 61, 29, texEnemy); // die sprite

	//LPANIMATION ani;

	//ani = new CAnimation(100);	// idle big right
	//ani->Add(10001);
	//animations->Add(400, ani);

	//ani = new CAnimation(100);	// idle big left
	//ani->Add(10011);
	//animations->Add(401, ani);

	//ani = new CAnimation(100);	// idle small right
	//ani->Add(10021);
	//animations->Add(402, ani);

	//ani = new CAnimation(100);	// idle small left
	//ani->Add(10031);
	//animations->Add(403, ani);

	//ani = new CAnimation(100);	// walk right big
	//ani->Add(10001);
	//ani->Add(10002);
	//ani->Add(10003);
	//animations->Add(500, ani);

	//ani = new CAnimation(100);	// // walk left big
	//ani->Add(10011);
	//ani->Add(10012);
	//ani->Add(10013);
	//animations->Add(501, ani);

	//ani = new CAnimation(100);	// walk right small
	//ani->Add(10021);
	//ani->Add(10022);
	//ani->Add(10023);
	//animations->Add(502, ani);

	//ani = new CAnimation(100);	// walk left small
	//ani->Add(10031);
	//ani->Add(10032);
	//ani->Add(10033);
	//animations->Add(503, ani);


	//ani = new CAnimation(100);		// ninja die
	//ani->Add(10099);
	//animations->Add(599, ani);

	//

	//ani = new CAnimation(100);		// brick
	//ani->Add(20001);
	//animations->Add(601, ani);

	//ani = new CAnimation(300);		// Goomba walk
	//ani->Add(30001);
	//ani->Add(30002);
	//animations->Add(701, ani);

	//ani = new CAnimation(1000);		// Goomba dead
	//ani->Add(30003);
	//animations->Add(702, ani);

	//ninja = new Cninja();
	//ninja->AddAnimation(400);		// idle right big
	//ninja->AddAnimation(401);		// idle left big
	//ninja->AddAnimation(402);		// idle right small
	//ninja->AddAnimation(403);		// idle left small

	//ninja->AddAnimation(500);		// walk right big
	//ninja->AddAnimation(501);		// walk left big
	//ninja->AddAnimation(502);		// walk right small
	//ninja->AddAnimation(503);		// walk left big

	//ninja->AddAnimation(599);		// die

	//ninja->SetPosition(0.0f, 0);
	//objects.push_back(ninja);

	//for (int i = 0; i < 5; i++)
	//{
	//	CBrick *brick = new CBrick();
	//	brick->AddAnimation(601);
	//	brick->SetPosition(100 + i*48.0f, 74);
	//	objects.push_back(brick);

	//	brick = new CBrick();
	//	brick->AddAnimation(601);
	//	brick->SetPosition(100 + i*48.0f, 90);
	//	objects.push_back(brick);

	//	brick = new CBrick();
	//	brick->AddAnimation(601);
	//	brick->SetPosition(84 + i*48.0f, 90);
	//	objects.push_back(brick);
	//}


	//for (int i = 0; i < 30; i++)
	//{
	//	CBrick *brick = new CBrick();
	//	brick->AddAnimation(601);
	//	brick->SetPosition(0 + i*16.0f, 150);
	//	objects.push_back(brick);
	//}

	//// and Goombas 
	//for (int i = 0; i < 4; i++)
	//{
	//	goomba = new CGoomba();
	//	goomba->AddAnimation(701);
	//	goomba->AddAnimation(702);
	//	goomba->SetPosition(200 + i*60, 135);
	//	goomba->SetState(GOOMBA_STATE_WALKING);
	//	objects.push_back(goomba);
	//}
//viewport->SetViewPortPosition(0, 100);
	viewport = new ViewPort(0,-30);



}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)

{
	ninja->Update(dt);
	//viewport->SetViewPortPosition(viewport->GetViewPortPosition().x, viewport->GetViewPortPosition().y-20);
	// We know that ninja is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	/*vector<LPGAMEOBJECT> coObjects;*/
	/*for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt,&coObjects);
	}*/
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
		tilemap->Render(viewport);
		ninja->Render(viewport);
		
		//for (int i = 0; i < objects.size(); i++)
		//	objects[i]->Render();

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


	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT*2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}