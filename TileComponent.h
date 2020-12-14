#pragma once

#include "ECS.h"
//#include "TransformComponent.h"
//#include "SpriteComponent.h"
#include "SDL.h"


class TitleComponent : public Component
{
public:
	//TransformComponent* transform;
	//SpriteComponent* sprite;
	//SDL_Rect tileRect;
	//int tileID;
	//const char* path;

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TitleComponent() = default;

	~TitleComponent()
	{
		SDL_DestroyTexture(texture);
	}

	TitleComponent(int srcX,int srcY,int xpos,int ypos,const char* path)
	{
		/*id=tag
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;
		//tst
		//we use the id now : it will assign the texture for us when we create a tile
		switch (tileID)
		{
		case 0:
			path = "assets/dirt.png";
			break;
		case 1:
			path = "assets/grass.png";
			break;
		case 2:
			path = "assets/water.png";
			break;
		default:
			break;*/
		texture = TextureManager::LoadTexture(path);
		
		position.x = xpos;
		position.y = ypos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 32;//that s the siez of the tile we are going to be take in
		
		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = 64;
	}

	void update() override
	{
		//update our destination x and y
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
		//that will draw our tile where we need it
	}

};


/*
	void init() override
	{
		//add our tranformComponent to the tile , and give them the size of init
		entity->addComponent<TransformComponent>((float)tileRect.x,(float)tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
	}
};*/