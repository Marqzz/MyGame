#include "Map.h"
#include "Game.h"
#include <fstream>

//#include "TextureManager.h"
//bravo MARCO :D
//in the future we can load our map from an external source 
//UPDATE:I've reached the future :D
/*int lvl1[20][25] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,2,1,2,1,2,0,1,2,2,1,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};//exemplu: grass-0;dirt-1;water-2  ^-default map*/
Map::Map()
{
	/*dirt = TextureManager::LoadTexture("assets/dirt.png");
	grass = TextureManager::LoadTexture("assets/grass.png");
	water = TextureManager::LoadTexture("assets/water.png");

	LoadMap(lvl1);
	//setam srcRect si destRect
	src.x = src.y = 0; // incepem de la 0
	src.w = dest.w = 32;
	src.h = dest.h = 32;

	dest.x = dest.y = 0;//it will change this everytime we draw*/
}

Map::~Map()
{
	//SDL_DestroyTexture(grass);
	//SDL_DestroyTexture(water);
	//SDL_DestroyTexture(dirt);
}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	/*for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 25; column++)
		{
			//assigment code , practic dam load la map(care este variabila globala)
			map[row][column] = arr[row][column];
		}
	}
	*/
	
	//when we read the file , we read it characther by character
	char c;
	std::fstream mapFile;//we need to store it somewhere
	mapFile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			srcY = atoi(&c) * 32;
			mapFile.get(c);
			srcX = atoi(&c) * 32;
			//Game::AddTile(atoi(&tile), x * 32, y * 32);
			Game::AddTile(srcX, srcY, x * 64, y * 64);

			mapFile.ignore();
		}
	}


	mapFile.close();
}

/*void Map::DrawMap()
{
	int type = 0;

	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 25; column++)
		{
			type = map[row][column];

			dest.x = column * 32;
			dest.y = row * 32;
			/*cand incepe sa deseneze , vom incepe din stanga sus , si se va raspundi cu cate 32

			switch (type)
			{
			case 0://water
				TextureManager::Draw(water, src, dest);
				break;
			case 1 :
				TextureManager::Draw(grass, src, dest);
				break;
			case 2:
				TextureManager::Draw(dirt, src, dest);
				break;
			default:
				break;
			}
		}
	}
}
*/

