#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
	// acum generam texture
	SDL_Surface* tempSurface = IMG_Load(texture);//asta creaza surface texture
	//cream texture
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	//clear and free the surface 
	SDL_FreeSurface(tempSurface);
	return tex;
}
void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
	//SDL_RenderCopy(Game::renderer, tex, &src, &dest);
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest,NULL,NULL,flip);
}
// de fiecare data cand avem nevoie sa dam load la o textura , folosim aceasta fct