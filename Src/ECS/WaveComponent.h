#pragma once
#include "ECS.h"
#include "SDL.h"
#include "Components.h"

class WaveComponent : public Component
{
private:
	TransformComponent* transform;
	SpriteComponent* sprite;

	float startVel;

	//int distance;
	//unsigned int startTime;
	
	//int velocity;
	/*int xpos;
	int ypos;
	int h;
	int w;
	int sc;*/

public: 

	//WaveComponent(int xpos, int ypos, int h, int w, int sc);
	WaveComponent(float sv);

	void init() override;

	void update() override;
};