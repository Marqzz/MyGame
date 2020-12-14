#pragma once
#include "Game.h"

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest,SDL_RendererFlip flip);
	// am facut functia statica "Draw" ca sa apelam de fiecare data o metoda astfel incat ea sa deseneze de fiecare data ceea ce vrem noi
};
