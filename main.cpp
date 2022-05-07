#pragma warning(disable: 4996)
#include "tile.h"
#include "stopwatch.h"


int main(int argc, char* argv[]) {
	SDL_Window* window;
	SDL_Renderer* renderer;
	initSDL(window, renderer);
	TTF_Init();
	bool exit = false;
	unsigned int difficulty;
	unsigned int menu(SDL_Renderer * renderer, bool* exit, const unsigned int SCREEN_WIDTH, const unsigned int SCREEN_HEIGHT);
	void game(SDL_Renderer * renderer, bool* exit, const unsigned int DIFFICULTY, const unsigned int SCREEN_WIDTH, const unsigned int SCREEN_HEIGHT);
	while (1) {
		difficulty = menu(renderer, &exit, SCREEN_WIDTH, SCREEN_HEIGHT);
		if (exit) break;
		game(renderer, &exit, difficulty, SCREEN_WIDTH, SCREEN_HEIGHT);
		if (exit) break;
	}
	quitSDL(window, renderer);
	TTF_Quit();
	return 0;
}