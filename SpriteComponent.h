#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Animation.h"
#include <map>//to hold the animation in the sprite component


class SpriteComponent : public Component
{
private:
	//we gonna need a refference to our possition this component is gonna be responsable to draw it to the screen
	TransformComponent* transform;
	SDL_Texture* texture;//we need to destroy this texture when it s done
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;//the delay between frames and milliseconds

public:

	int animIndex = 0;

	//"let`s hold the animation:
	std::map<const char*, Animation>animations;//this will take care of holding our animations for us

	//now we set a flag to for the animation to go in each way we want it
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(const char* path)//path to the texture we are gonna use
	{
		//here we have to load the texture
		//texture = TextureManager::LoadTexture(path);
		setTex(path);
	}

	SpriteComponent(const char* path,bool isAnimated)//int nFrames,int mSpeed)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 3, 100);
		Animation walk = Animation(1, 8, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		//frames = nFrames;
		//speed = mSpeed;

		Play("Idle");

		setTex(path);
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path)//setTexture
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{

		transform = &entity->getComponent<TransformComponent>();//we have acces to possition component

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
		//destRect.w = destRect.h = 64;
		//srcRect.w = srcRect.h = 32;

	}
	void update()override
	{
		//destRect.x = position->x();
		//destRect.y = position->y();

		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}
	void draw()override
	{
		TextureManager::Draw(texture, srcRect, destRect,spriteFlip);
	}

	void Play(const char* animName)
	{
		//we use this to change the current frames and index that we need
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}

};