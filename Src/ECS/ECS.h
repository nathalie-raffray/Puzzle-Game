#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u; //u for unsigned
	return lastID++; //get 1, 2, 3 each time we run it
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32; //so we can have 32 groups or layers

using ComponentBitSet = std::bitset<maxComponents>; //to see which components an entity has
using GroupBitset = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}
	
	virtual ~Component() {}
};

class Entity
{
private:
	Manager& manager;
	bool active = true; //if false, remove from game
	std::vector<std::unique_ptr<Component>> components; //can think of a vector as an array but with dynamic size

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitset groupBitset;

public:
	std::string name;

	Entity(Manager& mManager, std::string& n) : manager(mManager), name(n) {} //use lowercase mManager to tell the difference between manager and member manager
	
	void update()
	{
		for (auto& c : components) c->update();
	}
	void draw() {
		for (auto& c : components) c->draw();
	}
	bool isActive() const { return active; }
	void destroy() { active = false; }

	bool hasGroup(Group mGroup)
	{
		return groupBitset[mGroup]; //will return true or false if a certain bit is 1 or 0 in that bitset
	}

	void addGroup(Group mGroup);
	void delGroup(Group mGroup)
	{
		groupBitset[mGroup] = false;
		//in the manager, it checks to see if the bit is false, if it is
		//it will remove entity from that group
	}

	template <typename T> bool hasComponent() const
	{
		//return componentBitSet[getComponentID<T>];
	    return componentBitSet[getComponentTypeID<T>()];
		//has it got the component?
	
	}

	template <typename T, typename... TArgs> 
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		//so that when we add a component of a certain type, it will always be put in the same
		//position in the array
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template <typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]); 
		//so we set a pointer to a position in our component array
		return *static_cast<T*>(ptr);
		//this will allows us to do somethin glike
		//gameobject.getComponent<PositionComponent>().setXpos(25)
	}
};

class Manager
{

private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;
public:
	void update()
	{
		for (auto& e : entities) e->update();
	}
	void draw()
	{
		for (auto& e : entities) e->draw();
	}

	void refresh()
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity)
			{
				return !mEntity->isActive() || !mEntity->hasGroup(i);
			}), //remove_if will return an iterator pointing to the first of the
				//tail elements that can be removed
				std::end(v));
		}
		
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->isActive();
		}),
			std::end(entities)); //remove entities if they're not active
	}

	void AddToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}

	Entity& addEntity(std::string name)
	{
		Entity* e = new Entity(*this, name);
		std::unique_ptr<Entity> uPtr{ e }; //initialize uPtr to e
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};