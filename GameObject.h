#pragma once
#include "Game.h"

class GameObject {
public:GameObject(const char* texturesheet,int x,int y);
	//cand cream G.O.trebuie sa stim ce renderer folosim
	  ~GameObject();
	  void Update();//keep updating stuff in game class,fiecare obiect v-a primi update separat prin aceasta metoda ( fiecare cu treaba lui cum ar veni ) 
	  void Render();

private:int xpos;
	   int ypos;
	   SDL_Texture* objTexture;
	   SDL_Rect srcRect, destRect;//rect=rectangle
		//campurile de mai sus este ca sa-i dam display
	   //SDL_Renderer* renderer;-folosim staticul
};