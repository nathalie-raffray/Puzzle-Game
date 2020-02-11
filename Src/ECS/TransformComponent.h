#pragma once
#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{
	
public:

	Vector2D position;
	Vector2D velocity;


	//float rotZ = 0.0f; //in degrees
	//Vector2D centerRot = Vector2D(0, 0);

	int height = 32;
	int width = 32;
	float scale = 1.0f;

	int speed = 3;

	
	TransformComponent()
	{
		position.Zero();
	}

	TransformComponent(float sc)
	{  
		//position.Zero();
		//position.x = 400;
		//position.y = 320;
		scale = sc;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, float sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}


	/*TransformComponent(float x, float y, float rot, Vector2D& cr, int h, int w, float sc)
	{
		position.x = x;
		position.y = y;
		rotZ = rot;
		centerRot.x = cr.x;
		centerRot.y = cr.y;
		height = h;
		width = w;
		scale = sc;
	}*/


	void init() override
	{
		velocity.Zero();
	}


	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

};