#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <iostream>

class Game
{
public:

	Game();

	// Global event
	static SDL_Event event;

	bool Running()
	{
		return _running;
	}

	void handleEvents(int randomNumber,int randomAlien);
	void update();
	void render();
	void clean();

	void initializeAliens();

	// Check collision between two objects
	bool checkCollison(SDL_Rect a, SDL_Rect b);

private:
	bool _running;

};

#endif // GAME_H