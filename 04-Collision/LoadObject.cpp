#include "LoadObject.h"



void LoadObject::Load(string file, vector<LPGAMEOBJECT>* listObject)
{
	ifstream input;
	input.open(file, ifstream::in);

	string checkEnd;
	int id;
	int type;
	float x;
	float y;
	int width;
	int height;

	int count = 0;

	while (input >> checkEnd)
	{
		if (checkEnd == "END")
		{
			count++;
			continue;
		}
		if (count == 0)
		{
			id = atoi(checkEnd.c_str());
			input >> type >> x >> y >> width >> height;
			LoadObjects(id, type, x, y, width, height, listObject);
		}
	}
}

void LoadObject::LoadObjects(int id, int type, float x, float y, int width, int height, vector<LPGAMEOBJECT>* listObject)
{
	if (type == 4)
	{
		CGameObject *object;
		object = new CBrick();
		object->SetId(id);
		object->SetType(type);
		object->SetPosition(x, y);
		object->SetWidth(width);
		object->SetHeight(height);
		listObject->push_back(object);
	}
}

LoadObject::LoadObject()
{
}


LoadObject::~LoadObject()
{
}
