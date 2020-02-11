#pragma once
#include "ECS.h"
#include "Components.h"

//class KeyboardController;
//class PlanetComponent;

class ClockhandComponent: public Component
{
private:
	TransformComponent* transform;
	SpriteComponent* sprite;

	Entity* planetParent;
	TransformComponent* parentTransform;
	SpriteComponent* parentSprite;
	
	int height;
	int width;
	float scale;
	//Vector2D rotCenter;
	Vector2D pos;
	Vector2D pCenter;

public:

	Vector2D* start;
	Vector2D* finish;

	bool selected = false;

	void init() override;

	void update() override;
	
	ClockhandComponent(Entity* pp, Vector2D& p, int w, int h, float sc, bool sel);

	double calculateAngle();

	void keyboardEvents();

	void changeHand();

};