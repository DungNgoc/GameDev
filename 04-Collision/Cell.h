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
	void SetListObjects(vector<LPGAMEOBJECT> ob)
	{
		listObj = ob;
	}
};

class Cell;
typedef Cell * LPCELL;