#pragma once
#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent *transform;
	SpriteComponent* sprite;

	//KeyboardController();
	//~KeyboardController();

	void init() override;
	void update() override;
};