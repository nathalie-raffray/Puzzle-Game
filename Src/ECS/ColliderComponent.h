#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"
#include "../TextureManager.h"
#include "../Physics.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider; //pos in world space
	std::string tag;

	SDL_Texture* tex;
	SDL_Rect srcR, destR;

	Vector2D posObjectSpace = Vector2D(0,0);

	TransformComponent* transform = nullptr;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	ColliderComponent(std::string t, int xpos, int ypos, int size)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
		//originalPos = Vector2D(xpos, ypos);
	}

	ColliderComponent(std::string t, int xpos, int ypos, int size, Entity* entity)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
		//originalPos = Vector2D(xpos, ypos);
		transform = &entity->getComponent<TransformComponent>();
	}

	void init() override
	{
		
		if (!transform)
		{
			if (!entity->hasComponent<TransformComponent>()) transform = &entity->addComponent<TransformComponent>();
			else transform = &entity->getComponent<TransformComponent>();
		}
		
		posObjectSpace.x = collider.x - transform->position.x;
		posObjectSpace.y = collider.y - transform->position.y;

		tex = TextureManager::LoadTexture("assets/coltex.png");
		srcR = { 0, 0, 32, 32 };
		destR = { collider.x, collider.y, collider.w, collider.h };

		//originalPos = Vector2D(transform->position.x+195, transform->position.y+78);
		//originalPos = Vector2D(195, 78);

	}

	void update() override
	{
		if (tag != "terrain" && false) //CHANGE
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}
		
		destR.x = collider.x - Game::camera.x;
		destR.y = collider.y - Game::camera.y;

	}

	void draw() override
	{
		TextureManager::Draw(tex, srcR, destR, 0, SDL_Point{ 0, 0 }, SDL_FLIP_NONE);
	}

	void rotateAroundPoint(Vector2D point, double degrees);
};