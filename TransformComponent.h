#pragma once
#include "Components.h"
//am schimbat din "PositionComponent" in "TransformComponent"
//pt ca nu vrem diferite componente for rotation scale
//acuma TransformComponent will hold our position and rotation for scale 
#include "Vector2D.h"


class TransformComponent : public Component
{

public:

	Vector2D position;
	Vector2D velocity;
	
	int height = 32;//by default
	int width = 32;//by default
	int scale = 1;//by default

	int speed = 3;


	TransformComponent()
	{
		//by default : 
		//xpos = 0;
		//ypos = 0;
		//position.x = 0.0f;
		//position.y = 0.0f;
		position.Zero();
	}

	TransformComponent(int sc)
	{
		//position.x = 0.0f;
		//position.y = 0.0f;
		//position.Zero();
		position.x = 400;
		position.y = 320;//the middle of the screen
		scale = sc;
	}

	TransformComponent(float x, float y)
	{
		//position.x = x;
		//position.y = y;
		position.Zero();
	}

	TransformComponent(float x, float y,int h,int w,int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}
	//expose and be able to set our xpos and ypos
	//int x() {return xpos;}
	//int y() { return ypos; }
	//void init() override
	//{
	//	xpos = 0;
	//	ypos = 0;
	//}

	void init() override
	{
		//velocity.x = 0;
		//velocity.y = 0;
		velocity.Zero();
	}
	void update() override
	{
		//xpos++;
		//ypos++;
		//"spatiu"
		//here we move our player
		//position.x += velocity.x * speed;
		//position.y += velocity.y * speed;
		position.x += velocity.x * speed;//this will be able to move our player on the map again
		position.y += velocity.y * speed;
	}
	//void setPosition(int x, int y)
	//{
	//	xpos = x;
	//	ypos = y;
	//}
};