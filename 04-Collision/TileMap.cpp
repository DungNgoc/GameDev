#include "TileMap.h"
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 270


TileMap::TileMap(float _width, float _height, CSprite *_sprite, float _frameWidth, float _frameHeight)
{
	width = _width;
	height = _height;
	sprite = _sprite;

	frameWidth = _frameWidth;
	frameHeight = _frameHeight;

	spritePerRow =  (sprite->right-sprite->left+1)/ frameWidth;

	rows = height / frameHeight;
	cols = width / frameWidth;
	matrix = new int*[rows];
	for (int i = 0; i < rows; i++)
		matrix[i] = new int[cols];
}


TileMap::~TileMap()
{
	if (matrix)
	{
		for (int i = 0; i < rows; i++)
		{
			delete matrix[i];
		}
		delete matrix;
		matrix = nullptr;
	}

	if (sprite)
	{
		delete sprite;
		sprite = nullptr;
	}
}

void TileMap::LoadListTileFromFile(const char *file)
{
	fstream pFile;
	pFile.open(file, fstream::in);
	string lineString;
	int *posSpace = new int[cols];
	string subString;
	int i = 0;

	while (pFile.good())
	{
		getline(pFile, lineString);
		if (lineString.find("END") != string::npos)
			break;

		for (int j = 0; j < cols; j++)
		{
			if (j == 0)
			{
				posSpace[0] = lineString.find(" ", 0);
				subString = lineString.substr(0, posSpace[0]);
				int id = atoi(subString.c_str());
				matrix[i][j] = id;
			}
			else
			{	
				posSpace[j] = lineString.find(" ", posSpace[j - 1] + 1);
				subString = lineString.substr(posSpace[j - 1] + 1, posSpace[j] - (posSpace[j - 1] + 1));
				int id = atoi(subString.c_str());
				matrix[i][j] = id;
			}
		}
		i++;
	}
}


void TileMap::Render(ViewPort * viewport)
{
	RECT rect;
	D3DXVECTOR3 pos;

	
	D3DXVECTOR3 viewPortPosition = viewport->GetViewPortPosition();
	
	int rowStart;
	int rowEnd;
	int colStart;
	int colEnd;
	if ((viewPortPosition.y / frameHeight) < 0)
		rowStart = 0;
	else
		rowStart = (viewPortPosition.y / frameHeight);
	if ((viewPortPosition.y / frameHeight + SCREEN_HEIGHT / frameHeight + 1) >rows)
		rowEnd = rows;
	else
		rowEnd = (viewPortPosition.y / frameHeight + SCREEN_HEIGHT / frameHeight + 1);
	if ((viewPortPosition.x / frameWidth)<0)
		colStart = 0;
	else
		colStart = (viewPortPosition.x / frameWidth);
	if ((viewPortPosition.x / frameWidth + SCREEN_WIDTH / frameWidth + 1) > cols)
		colEnd = cols;
	else
		colEnd = (viewPortPosition.x / frameWidth + SCREEN_WIDTH / frameWidth + 1);

	for (int i = rowStart; i < rowEnd; i++)
	{
		for (int j = colStart; j < colEnd; j++)
		{
			rect.left = (matrix[i][j] % spritePerRow) * frameWidth;
			rect.top = (matrix[i][j] / spritePerRow) * frameHeight;
			rect.right = rect.left + frameWidth;
			rect.bottom = rect.top + frameHeight;
			pos.x = j * frameWidth;
			pos.y = i * frameHeight;
			pos.z = 0;
			pos = viewport->SetPositionInViewPort(pos);
			sprite->Draw(pos, rect);
		}
	}
}
