#pragma once
#include <vector>
#include "Sprites.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class TileMap
{
private:
	int **matrix;			
	int rows;				
	int cols;				
	float width;			
	float height;			
	float frameWidth;		
	float frameHeight;		
	int spritePerRow;
	CSprite *sprite;
public:
	TileMap(float _width, float _height, CSprite *_sprite, float _frameWidth, float _frameHeight);
	~TileMap();
	void LoadListTileFromFile(const char* file);
	//void Render(Camera *camera);
	void Render(ViewPort *viewport);
};

