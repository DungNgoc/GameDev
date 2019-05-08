#pragma once
#include "GameObject.h"
class Cell
{
	vector <LPGAMEOBJECT> listObj;
public:
	Cell();
	~Cell();
	void Insert(LPGAMEOBJECT object);
	vector<LPGAMEOBJECT> GetListObjects() { return listObj; }
};

class Cell;
typedef Cell * LPCELL;