#include "PlanetComponent.h"
#include "../Game.h"
#include "../Collision.h"

extern Manager manager;

PlanetComponent::PlanetComponent(float ms, float hs):
	minuteScale(ms), hourScale(hs)
{
	//i had code of init in here before and it was giving me an error but i dont know why, error at &(entity->getComponent.... where entity did not have any memory attached to it
}

void PlanetComponent::init()
{
	transform = &(entity->getComponent<TransformComponent>());
	sprite = &(entity->getComponent<SpriteComponent>());
	//collidercomp = &(entity->getComponent<ColliderComponent>());

	Vector2D wh = sprite->getDestWH(); //should there be an & here? holds width and height of destRect of sprite
	pCenter = Vector2D((transform->position.x + wh.x / 2), (transform->position.y + wh.y / 2));

	originalPosition = Vector2D(transform->position.x, transform->position.y);

	Animation idle(0, 1, 0);
	Animation clickedon(1, 1, 0);
	
	sprite->addAnimation(idle, "Idle");
	sprite->addAnimation(clickedon, "ClickedOn");

	minuteHand = &manager.addEntity("minuteHand");
	hourHand = &manager.addEntity("hourHand");

	Vector2D clockPos;
	
	//std::cout << "transformpos: " << transform->position << std::endl;
	//std::cout << "wh: " << wh << std::endl;
	std::cout << "pCenter: " << pCenter << std::endl;

	clockPos = Vector2D( -((clockhandW * minuteScale) / 2), -(clockhandH * minuteScale)) + pCenter;
	minuteHand->addComponent<ClockhandComponent>(entity, clockPos, clockhandW, clockhandH, minuteScale, false);
	//std::cout << "minuteHandPos: " << clockPos << std::endl;


	clockPos = Vector2D(-((clockhandW * hourScale) / 2), -(clockhandH * hourScale)) + pCenter;
	hourHand->addComponent<ClockhandComponent>(entity, clockPos, clockhandW, clockhandH, hourScale, true);
	//std::cout << "hourHandPos: " << clockPos << std::endl;

	minuteHand->addGroup(Game::groupClockhands);
	hourHand->addGroup(Game::groupClockhands);

	drawClockHands(false);

	tempFacingPoint = &(manager.addEntity("tempFacingPoint"));
	tempFacingPoint->addComponent<TransformComponent>(0.2f);
	tempFacingPoint->addComponent<SpriteComponent>("projectile");
	tempFacingPoint->addGroup(Game::groupDebugging);

}

void PlanetComponent::addColliderEntity1(Entity* c, int i)
{
	
	colliders1[i] = &c->getComponent<ColliderComponent>();
	//colliders[i]->transform = this->transform;
	/*static int i = 0;
	if (i < 3)
	{
		
		//c->getComponent<ColliderComponent>()
		//colliders[i]->posObjectSpace.x = colliders[i]->collider.x - transform->position.x;
		//colliders[i]->posObjectSpace.y = colliders[i]->collider.y - transform->position.y;
	}
	i++;*/

}

void PlanetComponent::addColliderEntity2(Entity* c, int i)
{
	colliders2[i] = &c->getComponent<ColliderComponent>();
}

void PlanetComponent::update()
{
	//originalPosition.x = static_cast<int>(transform->position.x) - Game::camera.x; //necessary for this level??
	//originalPosition.y = static_cast<int>(transform->position.y) - Game::camera.y;

	//centerRot.x = orcenterRot.x - Game::camera.x;
	//centerRot.y = orcenterRot.x - Game::camera.x;
	

	Vector2D wh = sprite->getDestWH();
	pCenter.x = transform->position.x + wh.x / 2; 
	pCenter.y = transform->position.y + wh.y / 2;

	if (selected && enabled)
	{
		Vector2D centerSprite = sprite->getDestWH();
		centerSprite.x /= 2;
		centerSprite.y /= 2;

		double degrees = minuteHand->getComponent<SpriteComponent>().degrees;
		
		if (minuteHand->getComponent<ClockhandComponent>().selected && minuteHandEnabled) //rotate on planet center
		{
			sprite->centerRot.x = sprite->getDestWH().x/2;
			sprite->centerRot.y = sprite->getDestWH().y/2;
			
			sprite->degrees = (int)degrees%360;
			//collidercomp->rotateAroundPoint(centerSprite, degrees);

		}
		else if(hourHandEnabled) //else, hour hand is selected. rotate on orbit
		{
			rotateOrbit();
			//collidercomp->rotateAroundPoint(centerSprite, degrees);
		}
		for (auto& c : colliders1)
		{
			if(c) c->rotateAroundPoint(centerSprite, degrees);
			
		}
		for (auto& c : colliders2)
		{
			if (c) c->rotateAroundPoint(centerSprite, degrees);

		}

		//std::cout << entity->name << " position: " << transform->position << std::endl;
		std::cout << entity->name << " angles: " << sprite->degrees << std::endl;
		
	}
	
	
}

bool PlanetComponent::isFacing(const PlanetComponent& other, int index)
{
	Vector2D centerSprite = sprite->getDestWH();
	centerSprite.x /= 2;
	centerSprite.y /= 2;

	Vector2D centerSpriteOther = other.sprite->getDestWH();
	centerSpriteOther.x /= 2;
	centerSpriteOther.y /= 2;

	double degrees = minuteHand->getComponent<SpriteComponent>().degrees; //rotating around center of sprite 
	//double degrees2 = hourHand->getComponent<SpriteComponent>().degrees; //rotating around centerRot
	double degreesOther = other.minuteHand->getComponent<SpriteComponent>().degrees; //rotating around center of sprite 

	if (entity->name == "leopardPlanet")
	{
		Vector2D p1(Physics::rotate(leopardFacingPoints[index], centerSprite, degrees));
		p1 += transform->position;
		Vector2D p2(Physics::rotate(other.facingPoint, centerSpriteOther, degreesOther));
		p2 += other.transform->position;

		tempFacingPoint->getComponent<TransformComponent>().position = p1;
		other.tempFacingPoint->getComponent<TransformComponent>().position = p2;

		p1 -= pCenter;
		p2 -= other.pCenter;
		p1.Normalize();
		p2.Normalize();

		

		float dot = p1.Dot(p2);

		if (dot < -0.99f)
		{
			//std::cout << entity->name << ": " << p1 << std::endl;
			//std::cout << other->entity->name << ": " << p2 << std::endl;

			//std::cout << "bplanet pcenter" << ": " << other->pCenter << std::endl;
			//std::cout << "bplanet facingp" << ": " << other->facingPoint << std::endl;
			return true;
		}
	}

	return false;
}



void PlanetComponent::rotateOrbit()
{
	//move to origin
	double degrees = hourHand->getComponent<SpriteComponent>().degrees;
	Vector2D v(Physics::rotate(originalPosition, centerRot, degrees));
	transform->position = v;
	
	/*Vector2D u(originalPosition.x - centerRot.x, originalPosition.y - centerRot.y);



	//std::cout << "degrees: " << degrees << std::endl;

	float s = sin(static_cast<float>(degrees * (M_PI / 180)));
	float c = cos(static_cast<float>(degrees * (M_PI / 180)));

	//std::cout << "sin : " << s << std::endl;
	//std::cout << "cos : " << c << std::endl;

	Vector2D v(0,0);
	v.x = c * u.x - s * u.y;
	v.y = s * u.x + c * u.y;

	v.Add(centerRot);*/

	

	/*std::cout << "oPosition: " << originalPosition << std::endl;
	std::cout << "centerRot: " << centerRot << std::endl;
	std::cout << "v: " << v << std::endl;*/

	//transform->position.x = v.x;
	//transform->position.y = v.y;

}


void PlanetComponent::drawClockHands(bool dch)
{
	minuteHand->getComponent<SpriteComponent>().enabled = dch;
	hourHand->getComponent<SpriteComponent>().enabled = dch;
}


bool PlanetComponent::isSelected(int x, int y) {

	return selected;
}

PlanetComponent* PlanetComponent::lastPlanetSelected = nullptr;

//auto& planets(man.getGroup(Game::groupPlanets));

void PlanetComponent::selectPlanet(int x, int y)
{
	if (sprite->isClicked(x, y))
	{
		
		if (lastPlanetSelected != nullptr && (lastPlanetSelected->entity->name != entity->name))
		{
			lastPlanetSelected->selected = false;
			lastPlanetSelected->handSel = 0;
			//minuteHand->getComponent<SpriteComponent>().enabled = true;
			lastPlanetSelected->drawClockHands(false);
			lastPlanetSelected->entity->getComponent<SpriteComponent>().Play("Idle");
		}
		this->selected = true; //change animation when selected
		this->handSel = 0;
		lastPlanetSelected = this; 

		drawClockHands(true);

		sprite->Play("ClickedOn");

		//std::cout << "is enabled?: " << sprite->enabled << std::endl;

		//minuteHand->getComponent<SpriteComponent>().enabled = true;
		//hourHand->getComponent<SpriteComponent>().enabled = true;
	}
}

void PlanetComponent::keyboardEvents()
{
	if (Game::event.type == SDL_MOUSEBUTTONDOWN)
	{
		selectPlanet(Game::event.button.x, Game::event.button.y);

	}
	
	if (selected)
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_q:
				minuteHand->getComponent<ClockhandComponent>().changeHand();
				hourHand->getComponent<ClockhandComponent>().changeHand();
				break;

			default:
				break;
			}
		}		
	}
}

/*void PlanetComponent::handlePlanetaryCollisions(const Entity& p1Col, const Entity& p2Col, Entity& p1, Entity& p2, int which)
{
	SDL_Rect& colRect1 = p1Col.getComponent<ColliderComponent>().collider;
	SDL_Rect& colRect2 = p2Col.getComponent<ColliderComponent>().collider;
	if (Collision::AABB(colRect1, colRect2))
	{
		//std::cout << "hit colliders" << std::endl;
		if (p1.getComponent<PlanetComponent>().isFacing(p2.getComponent<PlanetComponent>(), which-1))
		{
			std::cout << "collision" << std::endl;
			p1.getComponent<PlanetComponent>().enabled = false;
			p2.getComponent<PlanetComponent>().enabled = false;

		}
	}
	if (p1.getComponent<PlanetComponent>().isFacing(p2.getComponent<PlanetComponent>(), which - 1) 
		&& !p2.getComponent<PlanetComponent>().hourHandEnabled
		&& !p1.getComponent<PlanetComponent>().hourHandEnabled)
	{
		//std::cout << "collision" << std::endl;
		//p1.getComponent<PlanetComponent>().enabled = false;
		//p2.getComponent<PlanetComponent>().enabled = false;
		//p1.getComponent<PlanetComponent>().minuteHandEnabled = false;
		//p2.getComponent<PlanetComponent>().minuteHandEnabled = false;

	}
}*/

void PlanetComponent::handleCollision()
{
	/*if (abs(transform->position.x - restingPosition.x) < 2 && abs(transform->position.y - restingPosition.y) < 2 && hourHandEnabled)
	{
		hourHandEnabled = false;
	}
	if (abs(sprite->degrees - restingAngle) < 2 && minuteHandEnabled && !hourHandEnabled)
	{
		minuteHandEnabled = false;
	}*/
	if (abs(transform->position.x - restingPosition.x) < 2 && abs(transform->position.y - restingPosition.y) < 2 && hourHandEnabled
		&& abs( (((int)sprite->degrees + 360)%360) - restingAngle) < 2)
	{
		hourHandEnabled = false;
		minuteHandEnabled = false;
	}
	
}