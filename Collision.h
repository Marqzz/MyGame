#pragma once
#include <SDL.h>

class ColliderComponent;

class Collision
{
public:
	//we need to create the function to do this
	//we put it static cuz we want to get access to this function from other parts of this program
	//acces-allign-bounding-box
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
};