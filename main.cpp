#include "tile.h"
#include "stopwatch.h"


int main(int argc, char* argv[]) {
	SDL_Window* window;
	SDL_Renderer* renderer;
	initSDL(window, renderer);
	TTF_Init();
	Mix_Music* bgMusic = Mix_LoadMUS("audio/bgMusic.mp3");
	Mix_Music* menuMusic = Mix_LoadMUS("audio/menuMusic.mp3");
	Mix_Chunk* hitSound = Mix_LoadWAV("audio/hitSound.wav");
	bool exit = false;
	unsigned int difficulty;
	unsigned int menu(SDL_Renderer * renderer, bool* exit, const unsigned int SCREEN_WIDTH, const unsigned int SCREEN_HEIGHT);
	void game(SDL_Renderer * renderer, bool* exit, const unsigned int DIFFICULTY, const unsigned int SCREEN_WIDTH, const unsigned int SCREEN_HEIGHT);
	while (1) {
		//Mix_PlayMusic(menuMusic, -1);
		difficulty = menu(renderer, &exit, SCREEN_WIDTH, SCREEN_HEIGHT);
		if (exit) break;
		//Mix_PlayMusic(bgMusic, -1);
		game(renderer, &exit, difficulty, SCREEN_WIDTH, SCREEN_HEIGHT);
		if (exit) break;
	}
	quitSDL(window, renderer);
	TTF_Quit();
	return 0;
}