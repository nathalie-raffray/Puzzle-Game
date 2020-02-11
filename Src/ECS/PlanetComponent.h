#pragma once
#include "ECS.h"
#include "Components.h"
#include "../Vector2D.h"
#include "../Physics.h"

//class KeyboardController;
//class ClockhandComponent;


class PlanetComponent : public Component
{
private:
	Entity* minuteHand;
	Entity* hourHand;

	float minuteScale;
	float hourScale;

	int clockhandW = 320;
	int clockhandH = 640;

	static PlanetComponent* lastPlanetSelected;

	TransformComponent* transform;
	SpriteComponent* sprite;
	ColliderComponent* colliders1[3] = { nullptr };
	ColliderComponent* colliders2[3] = { nullptr };
	Vector2D pCenter;

	Vector2D originalPosition;

	Vector2D orcenterRot = Vector2D(700, 500);

	Entity* tempFacingPoint;
	

public: 

	bool enabled = true;
	bool minuteHandEnabled = true;
	bool hourHandEnabled = true;
	Vector2D centerRot;

	short handSel = 0;
	//handSel = 1 for minuteHand, handSel = 2 for hourHand
	float orbitDegrees;
	Vector2D rotatedPosition;

	Vector2D leopardFacingPoints[3];
	Vector2D facingPoint;

	Vector2D restingPosition;
	float restingAngle;

	bool selected = false;

	PlanetComponent(float ms, float hs);
	~PlanetComponent() {}

	void update() override;

	void init() override;

	void rotateHands(int x, int y);

	void drawClockHands(bool dch);

	void addColliderEntity1(Entity* c, int i);
	void addColliderEntity2(Entity* c, int i);

	bool isFacing(const PlanetComponent& other, int i);


    void selectPlanet(int x, int y);

	bool isSelected(int x, int y);

	void keyboardEvents();

	void rotateOrbit();

	//static void handlePlanetaryCollisions(const Entity& p1Col, const Entity& p2Col, Entity& p1, Entity& p2, int which);
	void handleCollision();
	

	
};

