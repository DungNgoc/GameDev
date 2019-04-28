#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "GameObject.h"

#include "Brick.h"

class LoadObject
{
	public:
	void Load(string file, vector<LPGAMEOBJECT> *listObject);
	void LoadObjects(int id, int type, float x, float y, int width, int height, vector<LPGAMEOBJECT>* listObject);
	
	LoadObject();
	~LoadObject();
};

