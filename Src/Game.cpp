#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>

Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Manager manager;

bool Game::isRunning = false;
SDL_Rect Game::camera = { 0, 0, 800, 640};

AssetManager* Game::assets = new AssetManager(&manager);

auto& player(manager.addEntity("player"));
auto& label(manager.addEntity("label"));
auto& labelMouseClick(manager.addEntity("mouseclickedPos"));

auto& planet0(manager.addEntity("leopardPlanet"));
auto& planet1(manager.addEntity("bluePlanet"));
auto& planet2(manager.addEntity("brownPlanet"));
auto& planet3(manager.addEntity("redPlanet"));

/*auto& p0col11(manager.addEntity("p0BlueCollider"));
auto& p0col12(manager.addEntity("p0BlueCollider"));
auto& p0col21(manager.addEntity("p0PurpleCollider"));
auto& p0col22(manager.addEntity("p0PurpleCollider"));
auto& p0col31(manager.addEntity("p0RedCollider"));
auto& p0col32(manager.addEntity("p0RedCollider"));

auto& p1col01(manager.addEntity("p1LeopardCollider"));
auto& p1col02(manager.addEntity("p1LeopardCollider"));
auto& p2col01(manager.addEntity("p2LeopardCollider"));
auto& p2col02(manager.addEntity("p2LeopardCollider"));
auto& p3col01(manager.addEntity("p3LeopardCollider"));
auto& p3col02(manager.addEntity("p3LeopardCollider"));*/

auto& wave1(manager.addEntity("wave"));
auto& wave2(manager.addEntity("wave"));
auto& wave3(manager.addEntity("wave"));
auto& wave4(manager.addEntity("wave"));
auto& wave5(manager.addEntity("wave"));
auto& wave6(manager.addEntity("wave"));

auto& circles(manager.addEntity("circles"));
auto& ring(manager.addEntity("ring"));


Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}

	if (TTF_Init() == -1)
	{
		std::cout << "ERROR : SDL_TTF" << std::endl;
	}

	//player = new GameObject("assets/player.png", 0, 0);
	//enemy = new GameObject("assets/enemy.png", 50, 50);
	assets->AddTexture("terrain", "assets/terrain_ss.png");
	assets->AddTexture("player", "assets/player_anims.png");
	assets->AddTexture("projectile", "assets/proj.png");
	assets->AddTexture("clockhand", "assets/handofclock2.png");
	assets->AddTexture("leopardPlanet", "assets/leopardPlanet2.png");
	assets->AddTexture("redPlanet", "assets/redPlanet2.png");
	assets->AddTexture("yellowPlanet", "assets/yellowPlanet.png");
	assets->AddTexture("purplePlanet", "assets/purplePlanet2.png");
	assets->AddTexture("brownPlanet", "assets/brownPlanet2.png");
	assets->AddTexture("bluePlanet", "assets/bluePlanet2.png");
	assets->AddTexture("kandinskyCircles", "assets/kadinskyCircles.png");
	assets->AddTexture("floor", "assets/tilefloor.png");
	assets->AddTexture("line", "assets/tiledLine.png");
	assets->AddTexture("wave", "assets/wave.png");
	assets->AddTexture("ring", "assets/ring.png");

	assets->AddFont("arial", "assets/arial.ttf", 16);

	//map = new Map("terrain", 3, 32);

	//map->LoadMap("assets/map.map", 25, 20);

	player.addComponent<TransformComponent>(350.0f, 300.0f, 32, 32, 4);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	SDL_Color black = { 0, 0, 0, 255 };

	label.addComponent<UILabel>(10, 10, "Test String", "arial", black);
	labelMouseClick.addComponent<UILabel>(10, 30, "Test String", "arial", black);

	assets->CreateProjectile(Vector2D(600, 600), Vector2D(2, 0), 200, 2, "projectile");

	//TransformComponent(float x, float y, float rot, Vector2D cr, int h, int w, int sc)

	//CreatePlanet(Entity & entity, Game::TransformComponentInfo & transform, Game::PlanetComponentInfo & planet, Game::ColliderInfo collider[], int numColliders)

	/*Game::ColliderInfo collider[] = {
			{ &p0col11, &p0col12, "bluePlanetCollider", 10},
			{ &p0col21, &p0col22, "purplePlanetCollider", 10},
			{ &p0col31, &p0col32, "redPlanetCollider", 10}
	};*/

	Vector2D leopardFacingPoints[] = { {195, 78}, { 74, 76 }, { 111,165 } };

	//475, 380		//ORIGINAL : 300, 185
	assets->CreatePlanet(planet0,
		TransformComponentInfo{ { 475, 345 }, 208, 1 },
		PlanetComponentInfo(0.2f, 0.3f, leopardFacingPoints, { 366, 292 }, { 298.103, 191.601 }, 0.0f),3
		//collider, 3
	);

	//682, 212 //ORIGINAL: 497, 232

	assets->CreatePlanet(planet1,
		TransformComponentInfo{ { 690, 212 }, 65, 1 },
		PlanetComponentInfo(0.1f, 0.2f, { 45, 48 }, { 584, 171 }, { 490.735, 235.951 }, 121.0f),1
		//{ &ColliderInfo(&p1col01, &p1col02, "leopardPlanetCollider", 10) }, 1
	);

	assets->CreatePlanet(planet2,
		TransformComponentInfo{ { 352, 259 }, 67, 1 },
		PlanetComponentInfo(0.1f, 0.2f, { 25, 4 }, { 213, 356 }, { 382, 362 }, 330.0f),1
		//{ &ColliderInfo(&p2col01, &p2col02, "leopardPlanetCollider", 10) }, 1
	);

	assets->CreatePlanet(planet3,
		TransformComponentInfo{ { 73.0, 280.0f }, 175, 1 },
		PlanetComponentInfo(0.1f, 0.2f, { 162, 110 }, { 234, 328 }, { 224.04, 160.293 }, 0.0f),1
		//{ &ColliderInfo(&p3col01, &p3col02, "leopardPlanetCollider", 10) }, 1
	);
	
	//wave5.addComponent<TransformComponent>(-90, 550, 155, 1050, 1);
	//wave5.addComponent<WaveComponent>(0.5f);

	wave1.addComponent<TransformComponent>(-50, 345, 155, 1050, 1);
	wave1.addComponent<WaveComponent>(-0.5f);
	wave2.addComponent<TransformComponent>(-90, 370, 155, 1050, 1);
	wave2.addComponent<WaveComponent>(0.5f);
	wave3.addComponent<TransformComponent>(-50, 400, 155, 1050, 1);
	wave3.addComponent<WaveComponent>(-0.5f);
	wave4.addComponent<TransformComponent>(-50, 445, 155, 1050, 1);
	wave4.addComponent<WaveComponent>(0.5f);
	

	circles.addComponent<TransformComponent>(150, 100, 472, 435, 1);
	circles.addComponent<SpriteComponent>("kandinskyCircles");

	ring.addComponent<TransformComponent>(300, 190, 208, 208, 1);
	ring.addComponent<SpriteComponent>("ring");
	//ring.addGroup(Game::groupPlanets);
	


}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders)); 
auto& projectiles(manager.getGroup(Game::groupProjectiles));
auto& planets(manager.getGroup(Game::groupPlanets));
auto& clockhands(manager.getGroup(Game::groupClockhands));
auto& debuggers(manager.getGroup(Game::groupDebugging));
auto& waves(manager.getGroup(Game::groupWaves));

void Game::handleEvents()
{

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}
}

int x, y;

void Game::update()
{
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	std::stringstream ss;
	ss << "Player position: " << playerPos;

	label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");

	std::stringstream ss2;
	ss2 << "Mouse clicked on : ";
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		//ss2 << "(" << event.button.x << ", " << event.button.y << ")";
		x = event.button.x;
		y = event.button.y;
	}
	ss2 << "(" << x << ", " << y << ")";
	labelMouseClick.getComponent<UILabel>().SetLabelText(ss2.str(), "arial");

	
	
	manager.refresh();
	manager.update();

	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}

	for (auto& p : projectiles)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider,
			p->getComponent<ColliderComponent>().collider))
		{
			std::cout << "proj hit player" << std::endl;
			p->destroy();
		}
	}

	camera.x = player.getComponent<TransformComponent>().position.x - 400; //taking out half the screen to have player in the middle
	camera.y = player.getComponent<TransformComponent>().position.y - 320;

	if (camera.x < 0) camera.x = 0;
	if (camera.y < 0) camera.y = 0;
	if (camera.x > camera.w) camera.x = camera.w;
	if (camera.y > camera.h) camera.y = camera.h;

	//PlanetComponent::handlePlanetaryCollisions(p0col11, p1col01, planet0, planet1, 1);
	//PlanetComponent::handlePlanetaryCollisions(p0col21, p2col01, planet0, planet2, 2);
	//PlanetComponent::handlePlanetaryCollisions(p0col31, p3col01, planet0, planet3, 3);
	planet0.getComponent<PlanetComponent>().handleCollision();
	planet1.getComponent<PlanetComponent>().handleCollision();
	planet2.getComponent<PlanetComponent>().handleCollision();
	planet3.getComponent<PlanetComponent>().handleCollision();



	/* TO HAVE SCROLLABLE TILE BACKGROUND
	Vector2D pVel = player.getComponent<TransformComponent>().velocity;
	int pSpeed = player.getComponent<TransformComponent>().speed;

	for (auto t : tiles) //to scroll tile background
	{
		t->getComponent<TileComponent>().destRect.x += -(pVel.x * pSpeed);
		t->getComponent<TileComponent>().destRect.y += -(pVel.y * pSpeed);
	} */


	
	
	//for (auto cc : colliders)
	//{
		
		//Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
		
		//if (Collision::AABB(player.getComponent<ColliderComponent>(), *cc))
		//{
			//player.getComponent<TransformComponent>().scale = 1;
			//player.getComponent<TransformComponent>().velocity * -1;
			//std::cout << "Wall Hit!" << std::endl;
		//}
	//}

	
}


void Game::render()
{
	SDL_RenderClear(renderer);
	//painters algorithm
	//SDL_RenderCopy(renderer, playerTex, NULL, &destR); //to draw one source rectangle from texture to destination rectangle on screen	
													//passing NULL, NULL makes the source rectangle the whole image, and the destination 
													//rectangle the whole screen

	//manager.draw(); not good, draws objects in order of creation
	ring.draw();
	for (auto& t : tiles)
	{
		t->draw();
	}
	for (auto& w : waves)
	{
		w->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}
	
	for (auto& p : projectiles)
	{
		p->draw();
	}
	for (auto& p : planets)
	{
		p->draw();
	}
	for (auto& c : clockhands)
	{
		c->draw();
	}
	for (auto& c : colliders)
	{
		//c->draw();
	}
	for (auto& d : debuggers)
	{
		//d->draw();
	}

	label.draw();
	labelMouseClick.draw();
	//wave1.draw();
	//circles.draw();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

