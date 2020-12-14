#include "GameObject.h"
#include "TextureManager.h"
GameObject::GameObject(const char* texturesheet,int x,int y) {
	//when we create a copy of our game obj and we need to assign the renderer
	//and its texture
	//assign renderer first
	//renderer = ren;
	//texture now
	objTexture = TextureManager::LoadTexture(texturesheet);//asta creeaza textura
	xpos = x;
	ypos = y;
}

void GameObject::Update()
{
	//aici se fac updaturile
	xpos++;
	ypos++;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}
void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
	//asta deseneaza textura
}