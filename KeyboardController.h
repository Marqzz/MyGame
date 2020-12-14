#pragma once

#include "Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component //inherit - MOSTENIRE DE LA POO ( INCA NU AM INVATAT )
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	//this is where we check what keys we have got
	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)//KEYDOWN-when the key is pressed
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;//-1:in transformComponents ,ex:speed is 3 , we are gonna add -1 * speed = -3 ceea ce va muta player up 3 pixels
				sprite->Play("Walk");
				break;
			case SDLK_a:
				transform->velocity.x = -1;//din aceeasi pricina ca mai sus
				sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_d:
				transform->velocity.x = 1;//acuma vine 1*speed ( care este 3 ) =1*3=3
				sprite->Play("Walk");
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				sprite->Play("Walk");
				break;
			default:
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP)//KEYUP-when the key is released
		{
			//mai sus , cand am atins "the key", facem miscarea
			//acuma , cand ii dam release , o RESETAM
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0; 
				sprite->Play("Idle");
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_d:
				transform->velocity.x = 0; 
				sprite->Play("Idle");
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				sprite->Play("Idle");
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
				//ca atunci cand apasam pe ESCAPE , jocul sa se inchida
			default:
				break;
			}
		}


	}
};