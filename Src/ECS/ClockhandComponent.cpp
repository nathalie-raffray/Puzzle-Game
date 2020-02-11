#include "ClockhandComponent.h"


ClockhandComponent::ClockhandComponent(Entity* pp, Vector2D& p, int w, int h, float sc, bool sel)
	: planetParent(pp), pos(p), height(h), width(w), scale(sc), selected(sel)
{
	
}

void ClockhandComponent::init()
{
	//rotCenter = Vector2D(width*scale/2, height*scale);
	
	transform = &entity->addComponent<TransformComponent>(pos.x, pos.y, height, width, scale); //this is gonna look weird and wrong
	sprite = &entity->addComponent<SpriteComponent>("clockhand", Vector2D(width * scale / 2, height * scale), 0);
	sprite->enabled = false;  

	parentTransform = &planetParent->getComponent<TransformComponent>();
	parentSprite = &planetParent->getComponent<SpriteComponent>();

	Vector2D wh = parentSprite->getDestWH();
	pCenter = Vector2D((parentTransform->position.x + wh.x / 2), (parentTransform->position.y + wh.y / 2));

	Animation idle(0, 1, 0);
	Animation clickedon(1, 1, 0);

	sprite->addAnimation(idle, "Idle");
	sprite->addAnimation(clickedon, "ClickedOn");

	//std::cout << "rotCenter: " << rotCenter << std::endl;

	if (selected) sprite->Play("ClickedOn");

	entity->addComponent<KeyboardController>();
	start = &Vector2D(0, 0);
	finish = &Vector2D(0, 0);
}

void ClockhandComponent::update()
{
	
	
	pCenter.x = parentTransform->position.x + parentSprite->getDestWH().x/2;
	pCenter.y = parentTransform->position.y + parentSprite->getDestWH().y/2;
	transform->position = Vector2D(-((width * scale) / 2), -(height * scale)) + pCenter;
	

		//pCenter = Vector2D((transform->position.x + wh.x / 2), (transform->position.y + wh.y / 2));
}

double ClockhandComponent::calculateAngle()
{
	double angle = acos(start->Dot(*finish) / (start->Magnitude() * finish->Magnitude()));
	return angle;
}

void ClockhandComponent::keyboardEvents()
{

	if (selected)
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_RIGHT:
				sprite->degrees += 1;
				break;

			case SDLK_LEFT:
				sprite->degrees -= 1;
				break;

			default:
				break;
			}
		}
	}
	

}

void ClockhandComponent::changeHand()
{
	selected = !selected;
	if (selected) sprite->Play("ClickedOn");
	else sprite->Play("Idle");
}