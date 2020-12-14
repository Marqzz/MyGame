
#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static void AddTile(int srcX, int srcY, int xpos,int ypos);
	static SDL_Renderer* renderer;
	static SDL_Event event;
	//punem static mai sus la event so we have only 1 instance of this event, and we will check this event in our controller class
	static std::vector<ColliderComponent*>colliders;
	static bool isRunning; 
	static SDL_Rect camera; 

private:
	//bool isRunning = false;
	int cnt = 0;
	SDL_Window* window;
	//SDL_Renderer* renderer; am pus in public , pt ca aveam prea multi copii , la acelasi pointer , si nu era ok
};