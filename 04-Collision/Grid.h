#pragma once
#include "Cell.h"
#include "GameObject.h"
class Grid
{
public:
	friend class CGameObject;
	int cellsizex;
	int cellsizey;
	LPCELL *cells;
	int rows;
	int columns;
	static Grid * __instance;
	vector <LPGAMEOBJECT> list_object;
public:
	Grid(int widthmap, int heightmap, int cellsizex, int cellsizey);
	~Grid();
	//void Update(LP)
	static Grid * GetInstance(int widthmap, int heightmap, int cellsizex, int cellsizey);
	void Add(vector <LPGAMEOBJECT> *listObject);
	//void GetListOfObjects(vector<LPGAMEOBJECT> *list_object, ViewPort *viewport);
	vector<LPGAMEOBJECT> GetListObjects(ViewPort *viewport);
	void DeleteCoObject();
};

