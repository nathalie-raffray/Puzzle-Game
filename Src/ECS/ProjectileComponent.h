#pragma once
#pragma once
#include "ECS.h"
#include "Components.h"
#include "../Vector2D.h"

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(int rng, int sp, Vector2D v) : range(rng), speed(sp), velocity(v)
	{}

	~ProjectileComponent()
	{
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
	}

	void update() override
	{
		distance += speed;

		if (distance > range)
		{
			std::cout << "Out of Range" << std::endl;
			entity->destroy();
		}
		//else if projectile is out of bounds
		else if (transform->position.x > (Game::camera.x + Game::camera.w) || //then its out of the right hand side of the screen
			transform->position.x < Game::camera.x ||
			transform->position.y > (Game::camera.y + Game::camera.h) || //then its out of the bottom of the screen
			transform->position.y < Game::camera.y
			)
		{
			/*std::cout << "transform position : (" << transform->position.x << ", " <<
				transform->position.y << ")" << std::endl;
			std::cout << "camera position : (" << Game::camera.x << ", " <<
				Game::camera.y << ")" << std::endl;
			std::cout << "camera width, height : (" << Game::camera.w << ", " <<
				Game::camera.h << ")" << std::endl;*/
			std::cout << "Out of Bounds" << std::endl;
			entity->destroy();
		}
	}


private:

	TransformComponent* transform;

	int range = 0;
	int speed = 0;
	int distance = 0;
	Vector2D velocity;
};