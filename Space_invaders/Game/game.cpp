#include "game.h"
#include "graphics.h"
#include "bullet.h"
#include "alien.h"


static std::vector<Bullet> bullets;
static std::vector<Alien> aliens1;
std::vector<Alien> aliens2;
std::vector<int> aliens1Xpos = { 250, 280, 310, 340, 370, 400, 430, 460, 490, 520, 550 };
int aliens1Ypos = 20;

Uint32 tempAlienTime = -1000;

Uint32 bulletStartTime = -1000;

SDL_Event Game::event;


Graphics graphics;
Player player;

Game::Game()
{
	_running = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialized...\n";
	}
}

SDL_Texture* playerTexture = graphics.loadMedia("C:/programming/c++/Space_invaders/media/player.png");
SDL_Texture* bulletTexture = graphics.loadMedia("C:/programming/c++/Space_invaders/media/bullet2.png");
SDL_Texture* alienTexture1 = graphics.loadMedia("C:/programming/c++/Space_invaders/media/alien1.png");

void Game::initializeAliens()
{
	// First line of aliens
	for (int i = 0; i < 11; i++)
	{
		aliens1.push_back(Alien());
		aliens1[i].alienXPos = aliens1Xpos[i];
		aliens1[i].alienYPos = aliens1Ypos;
	}
}

void Game::handleEvents(int randomNumber, int randomAlien)
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_running = false;
			break;

		default:
			break;
		}

		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_z:
				if ((SDL_GetTicks() - bulletStartTime) >= 450) {
					bulletStartTime = SDL_GetTicks();
					bullets.push_back(Bullet());
					bullets.back().bulletXpos = player.getXPos() + 8;
					bullets.back().bulletYpos = player.getYPos();
				}	
				break;
			}

		}
	
		player.handleEvent(event);

		if (randomAlien >= aliens1.size())
		{
			randomAlien = aliens1.size() - 1;
		}

		if ((SDL_GetTicks() - tempAlienTime) >= 3000 && randomNumber == 45 || randomNumber == 10 || ( 5 < randomNumber && randomNumber < 8)) {
			tempAlienTime = SDL_GetTicks();
			bullets.push_back(Bullet());
			bullets.back().bulletXpos = aliens1[randomAlien].alienXPos;
			bullets.back().bulletYpos = aliens1[randomAlien].alienYPos + 20;
			bullets.back().bulletVelY = -bullets.back().bulletVelY;
		}
	}

}

// Movement, check collisions and the state of everything
void Game::update()
{

	// Update player position
	player.move();
	
	// Check collisions between aliens and bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int j = 0; j < aliens1.size(); j++)
		{
			aliens1[j].alienCollisionBox.x = aliens1[j].alienXPos;
			aliens1[j].alienCollisionBox.y = aliens1[j].alienYPos;
			bullets[i].bulletCollider.x = bullets[i].bulletXpos;
			bullets[i].bulletCollider.y = bullets[i].bulletYpos;

			// Collision
			if (checkCollison(aliens1[j].alienCollisionBox, bullets[i].bulletCollider))
			{
				aliens1[j].isDestroyed = true;
				bullets[i].isDestroyed = true;
			}
		}
	}

	// Update bullet position and delete
	for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end();)
	{
		it->fire();

		if (it->isDestroyed) {
			it = bullets.erase(it);
		}
		else {
			++it;
		}
	}

	// Update positions of aliens, fire bullets and delete
	for (std::vector<Alien>::iterator it = aliens1.begin(); it != aliens1.end();)
	{
		it->alienMove();

		if (it->isDestroyed)
		{
			it = aliens1.erase(it);
		}
		else {
			++it;
		}

	}
}

void Game::render()
{
	SDL_RenderClear(graphics.getRenderer());

	// Draw here
	// draw player
	graphics.render(playerTexture, player.getXPos(), player.getYPos());
	for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it)
	{
		graphics.render(bulletTexture, it->bulletXpos, it->bulletYpos);
	}

	for (std::vector<Alien>::iterator it = aliens1.begin(); it != aliens1.end(); ++it)
	{
		graphics.render(alienTexture1, it->alienXPos, it->alienYPos);
	}

	SDL_RenderPresent(graphics.getRenderer());
}

void Game::clean()
{
	SDL_DestroyWindow(graphics.getWindow());
	SDL_DestroyRenderer(graphics.getRenderer());
	SDL_Quit();
	std::cout << "Bullet vector size: \n" << bullets.size() << std::endl;
	std::cout << "Aliens1 vector size: \n" << aliens1.size() << std::endl;
	std::cout << "Game Cleaned!\n";
}

bool Game::checkCollison(SDL_Rect a, SDL_Rect b)
{
	// Get left and right sides
	int leftA = a.x;
	int rightA = a.x + a.w;
	int leftB = b.x;
	int rightB = b.x + b.w;

	// Get top and bottom sides
	int topA = a.y;
	int bottomA = a.y + a.h;
	int topB = b.y;
	int bottomB = b.y + b.h;

	if (bottomA <= topB)
	{
		return false;
	}
	
	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	// if all tests were false
	return true;
}

