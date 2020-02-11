#include "AssetManager.h"
#include "ECS\Components.h"


AssetManager::AssetManager(Manager* man) : manager(man) {}

AssetManager::~AssetManager() {}

void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id)
{
	auto& projectile(manager->addEntity("projectile"));
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
	projectile.addComponent<SpriteComponent>(id, false);
	projectile.addComponent<ProjectileComponent>(range, speed, vel);
	projectile.addComponent<ColliderComponent>("projectile");
	projectile.addGroup(Game::groupProjectiles);
}

void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}

void AssetManager::AddFont(std::string id, std::string path, int fontSize)
{
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font* AssetManager::GetFont(std::string id)
{
	return fonts[id];
}


void AssetManager::CreatePlanet(Entity& entity, Game::TransformComponentInfo& transform, Game::PlanetComponentInfo& planet, int numColliders)
{
	entity.addComponent<TransformComponent>(transform.pos.x, transform.pos.y, transform.dimension, transform.dimension, transform.scale);
	entity.addComponent<SpriteComponent>(entity.name);
	entity.addComponent<KeyboardController>();
	PlanetComponent* pcomp = &entity.addComponent<PlanetComponent>(planet.ms, planet.hs);
	entity.addGroup(Game::groupPlanets);
	
	pcomp->facingPoint = Vector2D(planet.facingPoint);
	std::memcpy(pcomp->leopardFacingPoints, planet.leopardFacingPoints, sizeof(Vector2D) * 3); //deep copy

	pcomp->centerRot = planet.centerRot;
	pcomp->restingPosition = planet.restingPos;

	pcomp->restingAngle = planet.degrees;

	/*if (entity.name == "redPlanet")
	{
		entity.getComponent<SpriteComponent>().degrees = 25;
	}*/

	//float radius = (transform.dimension * transform.scale) / 2;
	//Vector2D offset;
	
	/*for (int i = 0; i < numColliders; i++)
	{
		if (numColliders == 1) offset = planet.facingPoint * transform.scale;
		else offset = planet.leopardFacingPoints[i] * transform.scale;

		if (!collider[i].colliderEntity1->hasComponent<ColliderComponent>())
		{
			collider[i].colliderEntity1->addComponent<TransformComponent>();
			collider[i].colliderEntity1->addComponent<ColliderComponent>(collider[i].name, offset.x+transform.pos.x, offset.y+transform.pos.y, collider[i].size, &entity);
			pcomp->addColliderEntity1(collider[i].colliderEntity1, i);
			collider[i].colliderEntity1->addGroup(Game::groupColliders);
		}	

		if (!collider[i].colliderEntity2->hasComponent<ColliderComponent>())
		{
			//offset -= transform.pos;
			/*offset.x -= transform.dimension / 2;
			offset.y -= transform.dimension / 2;
			offset.Normalize();
			offset.x *= radius + transform.dimension/2;
			offset.y *= radius + transform.dimension / 2;

			collider[i].colliderEntity2->addComponent<TransformComponent>();
			collider[i].colliderEntity2->addComponent<ColliderComponent>(collider[i].name, offset.x+transform.pos.x, offset.y+transform.pos.y, collider[i].size, &entity);
			pcomp->addColliderEntity2(collider[i].colliderEntity2, i);
			collider[i].colliderEntity2->addGroup(Game::groupColliders);*/
			
	/*	}
	}*/
	

}
//planet0.getComponent<PlanetComponent>().addColliderEntity(&p0col1);

