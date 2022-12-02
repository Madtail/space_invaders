#include "game.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->initializeAliens();
	SDL_ShowCursor(SDL_DISABLE);
	srand(time(NULL));
	// Game loop
	while (game->Running())
	{
		frameStart = SDL_GetTicks();
		int randomNumber = rand() % 50 + 1;
		int randomAlien = rand() % 10 + 0;

		game->handleEvents(randomNumber, randomAlien);
		game->update();
		game->render();
		
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	delete game;
	return 0;
}