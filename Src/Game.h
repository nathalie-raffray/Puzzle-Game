#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include "Vector2D.h"

class ColliderComponent;
class AssetManager;
class Entity;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();


	static SDL_Renderer *renderer;
	static SDL_Event event; //only one instance of it!
	static bool isRunning;
	static SDL_Rect camera;
	static AssetManager *assets;

	enum groupLabels : std::size_t //can make up to 32 of these
	{								//by default, the first value is assigned 0, the next one is assigned 1, and so on
		groupMap,
		groupPlayers,
		groupColliders, 
		groupProjectiles, 
		groupPlanets, 
		groupClockhands,
		groupWaves,
		groupDebugging
	};

	struct TransformComponentInfo
	{
		const Vector2D pos;
		const int dimension;
		float scale;

	};

	struct PlanetComponentInfo
	{
		float ms;
		float hs;
		Vector2D facingPoint;
		Vector2D leopardFacingPoints[3];
		Vector2D centerRot;
		Vector2D restingPos;
		float degrees;
		PlanetComponentInfo(float m, float h, Vector2D fp, Vector2D cr, Vector2D rs, float d)
		{
			ms = m;
			hs = h;
			facingPoint= Vector2D(fp);
			for(int i = 0; i<3;i++) leopardFacingPoints[i] = {0,0};
			centerRot = Vector2D(cr);
			restingPos = Vector2D(rs);
			degrees = d;
		}
		PlanetComponentInfo(float m, float h, Vector2D fp[], Vector2D cr, Vector2D rs, float d)
		{
			ms = m;
			hs = h;
			facingPoint = { 0,0 };
			std::memcpy(leopardFacingPoints, fp, sizeof(Vector2D) * 3);
			centerRot = Vector2D(cr);
			restingPos = Vector2D(rs);
			degrees = d;
		}
	};

	/*struct ColliderInfo
	{
		Entity* colliderEntity1;
		Entity* colliderEntity2;
		std::string name;
		int size;
		

		ColliderInfo(Entity* e1, Entity* e2, std::string n, int s)
		{
			colliderEntity1 = e1;
			colliderEntity2 = e2;
			name = n;
			size = s;
			
		}
	};*/

	
		

private:
	int cnt = 0;
	SDL_Window *window;
	
};