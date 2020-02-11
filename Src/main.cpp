#include "Game.h"
#include "math.h"

Game *game = nullptr;

class Test {
public: 
	Test(std::size_t aa, std::size_t bb) {
		a = aa;
		b = bb;
	}
	size_t a;
	size_t b;
};

int main(int argc, char *argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS; //time between frames

	Uint32 frameStart;
	int frameTime;

	//Test* t = new Test(5, 3);
	
	//size_t c[5];
	//int hash[174999999];
	//std::cout << "size of *t: " << sizeof(*t) << std::endl;
	//std::cout << "size of t: " << sizeof(t) << std::endl;
	//std::cout << "size of int: " << sizeof(int) << std::endl;
	//std::cout << "size of c: " << sizeof(c) << std::endl;
	//std::cout << "size of size_t: " << sizeof(size_t) << std::endl;
	
	game = new Game();
	game->init("GameWindow", 800, 640, false);

	while (game->running())
	{
		frameStart = SDL_GetTicks();
		
		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	return 0;
}