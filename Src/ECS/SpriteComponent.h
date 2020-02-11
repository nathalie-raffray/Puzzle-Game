#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>
#include "../AssetManager.h"
#include <math.h>


class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0; //frames of the animation
	int speed = 100; //delay between frames in milliseconds	

public:

	bool enabled = true;
	double degrees = 0;
	SDL_Point centerRot = { 0, 0 };
	
	int animIndex = 0;
	std::map<const char*, Animation> animations;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE; //which way to flip sprite
	
	SpriteComponent() = default;
	SpriteComponent(std::string id) //path to the texture we're going to use
	{
		setTex(id);
	}

	SpriteComponent(std::string id, Vector2D& cr, double d) //path to the texture we're going to use
	{
		setTex(id);
		centerRot.x = cr.x;
		centerRot.y = cr.y;
		degrees = d;
	}

	SpriteComponent(std::string id, bool isAnimated)  
	{
		animated = isAnimated;
		setTex(id);

		if (animated)
		{
			Animation idle = Animation(0, 3, 100);
			Animation walk = Animation(1, 8, 100);

			animations.emplace("Idle", idle);
			animations.emplace("Walk", walk);

			Play("Idle");
		}


	}

	~SpriteComponent()
	{
		//SDL_DestroyTexture(texture); we dont want to do this now, because texture could be pointing to a texture used by multiple objects
	}

	void setTex(std::string id) //to change texture, ex: change rock tile to broken rock tile
	{
		texture = Game::assets->GetTexture(id);
	}

	void addAnimation(Animation a, const char* animName)
	{
		animations.emplace(animName, a);
	}

	void init() override
	{
		
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &(entity->getComponent<TransformComponent>()); //WHY &ENTITY AND NOT ENTITY
		
		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;

	}

	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
		
		srcRect.y = animIndex * transform->height;

		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;

		/*if (transform->rotZ > 0.001f) { //code for updating a rotated position
			float s = sin(static_cast<float>(transform->rotZ * 180 / M_PI));
			float c = cos(static_cast<float>(transform->rotZ * 180 / M_PI));

			Vector2D pos(transform->position);
			//Vector2D center(pos);
			//center.Subtract(Vector2D(destRect.w / 2, destRect.h / 2)); 

			//translate point to origin
			pos.Subtract(transform->centerRot);

			//rotate point about origin
			float xnew = pos.x * c - pos.y * s;
			float ynew = pos.x * s + pos.y * c;

			//translate point back
			transform->position.x = xnew + transform->centerRot.x;
			transform->position.y = ynew + transform->centerRot.y;

			transform->rotZ = 0.0f;
		}*/

		//degrees = transform->rotZ;
		//centerRot.x = (int)transform->centerRot.x;
		//centerRot.y = (int)transform->centerRot.y;

		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
		
	}

	void draw() override
	{
		if ((entity->name == "minuteHand" || entity->name == "hourHand") && enabled)
		{
			//std::cout << "here!! " << std::endl;
		}
		if(enabled) TextureManager::Draw(texture, srcRect, destRect, degrees, centerRot, spriteFlip);	
	}


	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}

	bool isClicked(int x, int y)
	{
		if (x > destRect.x && x < destRect.x + destRect.w
			&& y > destRect.y && y < destRect.y + destRect.h) return true;
		return false;
	}

	Vector2D getDestWH()
	{
		return Vector2D(destRect.w, destRect.h);
	}
};