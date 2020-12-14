#pragma once
//ECS - Entity Component System
//This is a bit of a jump in the learning curve! Basically, the ECS idea lets you organise memory so that it can be passed to the CPU in the most efficient way. The way a CPU accesses memories uses a few levels of caching (L1, L2 etc) with L1 being the smallest but the closest to the CPU (so, the fastest). It is most expensive to read from RAM, so arranging things so they can be passed in little contiguous chunks reduces 'cache misses'. For a better definition, look up Chandler Carruth, or 'CPU cache lines'.
#include <iostream>
#include <vector> // ??
#include <memory> // ??
#include < algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;


//pentru fiecare componenta : positia , fizica , AI , id

using ComponentID = std::size_t;

//need to generate ComponentID:
//the function below will be put in the place where we can use it

using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;//initialization ?
	//de fiecare data cand ii dam call , lastID va primi ID-ul de din inainte
	return lastID++;//every-time we call it , we will get the next one
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	//static ComponentID typeID = getComponentTypeID();
	// it will generate a new last ID for us and put back that ID
	
	static_assert (std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getNewComponentTypeID();

	return typeID;
}

//if an enetity has a component attached , function below
constexpr std::size_t maxComponents = 32;
//constexpr -> constant expression
constexpr std::size_t maxGroups = 32; // maxim de 32 de grupe "or" layers

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;//array-just an array, with the vector itself and maxComponents
// cu acestea , vom putea 
// daca vrem sa aflam if the next entity has got a selection of components we will have to compare if it has or not 


class Component
{
public:
	Entity* entity;// a refferance to its owner

	virtual void init() {} // we can call init function to get acces to all components
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}


};
class Entity
{
private:
	//manager reference : 
	Manager& manager;
	bool active = true;//aici vedem daca entitatea exista,daca este false , putem sa o stergem din game
	std::vector<std::unique_ptr<Component>> components; //list of components

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitset;//now each entity has a groupBitset
public:
	Entity(Manager& mManager) : manager(mManager) {}


	void update() {
		// we will do here: entity loop throu all components and call udate draw methods
		for (auto& c : components) c->update();
		
	}
	void draw() {
		for (auto& c : components) c->draw();
	}
	bool isActive()const { return active; }
	void destroy() { active = false; }

	// we have to check if it is in a group
	bool hasGroup(Group mGroup)
	{
		return groupBitset[mGroup];//return true or false , if a certain bit is 0 or 1 in that bitset
	}
	//add something to a group / remove something from a grouup
	void addGroup(Group mGroup);
	void delGroup(Group mGroup)
	{
		groupBitset[mGroup] = false;
	}


	template <typename T> bool hasComponent() const 
	{
		return componentBitSet[getComponentTypeID<T>()];
		//inainte era : " return componentBitSet[getComponent<T>]; imi dadea eroare de sintaxa , la " ] " , spunea ca expected an expression 
		//it will return true/false , asta este sa vedem daca are componente
	}
	//add a component to our entity
	template <typename T,typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component>uPtr{ c };
		components.emplace_back(std::move(uPtr));
		componentArray[getComponentTypeID<T>()] = c;
			//intre < si > sunt parametrii , cred , kind of
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		//set a pointer to get our possition array
		return *static_cast<T*>(ptr);
	}
	/*we got our entity class wich keeps a list of components*/
	//now we have to manager class wich keeps a list of our entities
};
class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;
public:
	void update()
	{
		//manager to update all of our entities
		for (auto& e : entities) e->update();
	}
	void draw()
	{
		//manager to draw all of our entities
		for (auto& e : entities) e->draw();
	}
	// we need our manager to get every frame , move throu our enteties and remove the ones that aren t there
	void refresh()
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v), [i](Entity* mEntity)
					{
						return !mEntity->isActive() || !mEntity->hasGroup(i);
					}),
				std::end(v));
			
		}


		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
		//that above will remove entities if they are not active
	
	}
	
	void AddToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);
		//that will add our entity to the group
	}

	std::vector<Entity*>& getGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
		//that will give us the list of our entities in a group
	}

	//we need to be able to add an entity to the world throu our manager class
	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity>uPtr{ e };
			//explication:unique_ptr<type of the pointer>nameOfVariable{initialization with}
		// now we created an entity , now to add this entity to our list
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};