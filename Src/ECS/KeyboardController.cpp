#include "KeyboardController.h"

void KeyboardController::init() 
{
	transform = &(entity->getComponent<TransformComponent>());
	sprite = &(entity->getComponent<SpriteComponent>());
}

void KeyboardController::update() 
{
	if (entity->hasComponent<PlanetComponent>())
	{
		entity->getComponent<PlanetComponent>().keyboardEvents();
		
		//if (Game::event.type == SDL_KEYDOWN) std::cout << "hello" << std::endl;
		/*if (Game::event.type == SDL_MOUSEBUTTONDOWN)
		{		
			std::cout << "Planet touched?" << std::endl;
			entity->getComponent<PlanetComponent>().selectPlanet(Game::event.button.x, Game::event.button.y);

		}
		if (Game::event.type == SDL_MOUSEBUTTONUP)
		{

		}
		if (Game::event.type == SDL_MOUSEMOTION)
		{
			//entity->getComponent<PlanetComponent>().rotateHands(Game::event.button.x, Game::event.button.y);
		}*/


	}

	if (entity->hasComponent<ClockhandComponent>() && sprite->enabled)
	{
		entity->getComponent<ClockhandComponent>().keyboardEvents();
		
		/*if (Game::event.type == SDL_MOUSEBUTTONDOWN)
		{
			//entity->getComponent<ClockhandComponent>().start->x = Game::event.button.x;
			//entity->getComponent<ClockhandComponent>().start->y = Game::event.button.y;
			//entity->getComponent<ClockhandComponent>().finish->x = Game::event.button.x;
			//entity->getComponent<ClockhandComponent>().finish->y = Game::event.button.y;
		}

		if (Game::event.type == SDL_MOUSEMOTION)
		{
			if (Game::event.motion.state & SDL_BUTTON_LMASK)
			{
				// mouse moved with left button down
				entity->getComponent<ClockhandComponent>().start->x = Game::event.motion.x - Game::event.motion.xrel;
				entity->getComponent<ClockhandComponent>().start->y = Game::event.motion.y - Game::event.motion.yrel;

				entity->getComponent<ClockhandComponent>().finish->x = Game::event.motion.x;
				entity->getComponent<ClockhandComponent>().finish->y = Game::event.motion.y;

			}
		}

		if (Game::event.type == SDL_MOUSEBUTTONUP)
		{
			entity->getComponent<ClockhandComponent>().start->Zero();
			entity->getComponent<ClockhandComponent>().finish->Zero();
		}*/
	}
    static std::string p = "player";
	//std::string c = "player";
	if (Game::event.type == SDL_KEYDOWN)
	{
		
		//std::cout << "keydown" << std::endl;
		//if (entity->getComponent<ColliderComponent>().tag == p)
		if(entity->name == p)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				sprite->Play("Walk");
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->Play("Walk");
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				sprite->Play("Walk");
				break;
			default:
				break;
			}
		}
		
	}

	if (Game::event.type == SDL_KEYUP)
	{
		//if (entity->getComponent<ColliderComponent>().tag == p)
		if (entity->name == p)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				sprite->Play("Idle");
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				sprite->Play("Idle");
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
				break;
			default:
				break;
			}
		}
		
		
	}

}