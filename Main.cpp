#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	const int FPS = 60;//frameuri constante 
	const int frameDelay = 1000 / FPS;//ne da timpul maxim intre frameuri
	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("GameWindow", 800, 640, false);

	while (game->running())
	{
		frameStart = SDL_GetTicks();//ne da cate milisecunde au fost de cand am initializat SDL

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;//ne da cat timp a fost pana sa randeze imaginea , sa faca updateuri , etc

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);//asta e comanda care ne da delay la frameuri
		}
	}
	//system("PAUSE");
	game->clean();
	return 0;
}