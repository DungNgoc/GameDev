#include "Grid.h"
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240



Grid * Grid::__instance = NULL;
Grid * Grid::GetInstance(int widthmap, int heightmap, int cellsizex, int cellsizey)
{
	if (__instance == NULL) __instance = new Grid(widthmap, heightmap, cellsizex,cellsizey);
	return __instance;
}

Grid::Grid(int widthmap, int heightmap, int cellsizex, int cellsizey)
{
	this->cellsizey = cellsizey;
	this->cellsizex = cellsizex;
	rows = heightmap / cellsizey;
	columns = widthmap / cellsizex;
	cells = new Cell*[rows];
	for (int i = 0; i < rows; i++)
		cells[i] = new Cell[columns];
}

Grid::~Grid()
{
}

void Grid::Add(vector<LPGAMEOBJECT>* listObject)
{
	for (int i = 0; i < listObject->size(); i++)
	{
		int cellY = (int)(listObject->at(i)->x / cellsizex);
		int cellX = (int)(listObject->at(i)->y / cellsizey);

		int cellY1 = (int)((listObject->at(i)->x + listObject->at(i)->GetWidth()) / cellsizex);
		int cellX1 = (int)((listObject->at(i)->y + listObject->at(i)->GetHeight()) / cellsizey);
		if (cellX == cellX1)
		{
			if (cellY != cellY1)
				for (int k = cellY; k < cellY1; k++)
					cells[cellX][k].Insert(listObject->at(i));
			else if (cellY == cellY1)
				cells[cellX][cellY].Insert(listObject->at(i));
		}
		else if (cellX != cellX1)
		{
			if (cellY != cellY1)
				for (int j = cellX; j < cellX1; j++)
					for (int k = cellY; k < cellY1; k++)
						cells[j][k].Insert(listObject->at(i));
			else if (cellY == cellY1)
			{
				for (int j = cellX; j < cellX1; j++)
					cells[j][cellY].Insert(listObject->at(i));
			}
		}
	}
}

void Grid::GetListOfObjects(vector<LPGAMEOBJECT>* list_object, ViewPort * viewport)
{

	list_object->clear();
	int xs, ys;
	int xe, ye;
	int i, j, k;
	xs = (int)viewport->GetViewPortPosition().x / cellsizex;
	ys = (int)viewport->GetViewPortPosition().y / cellsizey;

	xe = (int)(viewport->GetViewPortPosition().x + SCREEN_WIDTH) / cellsizex;
	ye = (int)(viewport->GetViewPortPosition().y + SCREEN_HEIGHT) / cellsizey;
	/*if (xe == columns - 1)
		xe += 1;*/
	for (i = ys; i < ye; i++)
		for (j = xs; j <= xe; j++)
		{
			if (cells[i][j].GetListObjects().size() != 0)
				for (k = 0; k < cells[i][j].GetListObjects().size(); k++)
				{
					LPGAMEOBJECT e = cells[i][j].GetListObjects()[k];
					list_object->push_back(e);
				}
			
		}
}
