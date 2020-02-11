#include "WaveComponent.h"

WaveComponent::WaveComponent(float sv) : startVel(sv)
{
	
}

void WaveComponent::init()
{
	transform = &entity->getComponent<TransformComponent>();
	sprite = &entity->addComponent<SpriteComponent>("wave");
	transform->speed = 1;
	transform->velocity.x = startVel;
	transform->velocity.y = 0;
	if (startVel < 0) sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
	entity->addGroup(Game::groupWaves);
}

void WaveComponent::update()
{
	if (transform->position.x <= -90)
	{
		transform->velocity.x *= -1;
	}
	else if (transform->position.x >= -10)
	{
		transform->velocity.x *= -1;
	}
	
	//transform->position.x = velocity * 
}