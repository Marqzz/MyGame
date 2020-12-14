#pragma once
#include <string>
#include "SDL.h"
//#include "ECS.h"
#include "Components.h"

class ColliderComponent : public Component //"Component"vine din ECS.h
{
	//firstly , we have to represent an area to be collidable
	//we will use SDLRct
public:
	SDL_Rect collider;
	std::string tag;
	//the tag will allow us to when we detect the collison we will prop the tag from the object we hit to find out wich object it is
	//every "entity" will have a tag

	TransformComponent* transform;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
		//daca nu are entitatea vreun component, trebuie neaparat sa-i punem una , pt ca altfel primim RUNTIME ERROR
	
		Game::colliders.push_back(this);//this will this component into the collider
	}

	void update() override
	{ 
		//mai jos we update the collider size and position
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->width * transform->scale;
		collider.h = transform->height*transform->scale;
	}

private:


};