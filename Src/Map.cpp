#include "Map.h"
#include "Game.h"
#include <fstream>
#include "ECS\ECS.h"
#include "ECS\Components.h"


extern Manager manager; //we're going to have a manager object
						//that is defined somewhere else
						//this one is the same as the one in Game.cpp

Map::Map(std::string tID, int ms, int ts) : texId(tID), mapScale(ms), tileSize(ts)
{
	scaledSize = ms * ts;
}

Map::~Map()
{
	
}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char c; 
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			srcY = atoi(&c) * tileSize;
			mapFile.get(c);
			srcX = atoi(&c) * tileSize;
			AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
			//std::cout << atoi(&tile) << ", ";
			mapFile.ignore(); //ignore comma
		}
		//mapFile.ignore();
		//std::cout << std::endl;
	}

	mapFile.ignore();

	for (int y = 0; y < sizeY; y++) //this is for our tile colliders
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			if (c == '1')
			{
				auto& tcol(manager.addEntity("tilecollider"));
				tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				tcol.addGroup(Game::groupColliders);
			}
			mapFile.ignore(); //if its a 0
		}
	}

	mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity("tile"));
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texId);
	tile.addGroup(Game::groupMap);
}

