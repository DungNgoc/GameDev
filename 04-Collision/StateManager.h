#pragma once
class StateManager
{
private:
	GameState * gameState;

public:
	static int stateID;
	static LPDIRECT3DDEVICE9 d3ddv;
	static LPD3DXSPRITE spriteHandler;
public:
	StateManager(LPDIRECT3DDEVICE9 d3ddv, LPD3DXSPRITE spriteHandler);
	~StateManager();
	void LoadState(int stateID, Simon *simon);
	void NextStateLevel();
	void Render(Camera *camera);
	void Update(DWORD dt);
};

