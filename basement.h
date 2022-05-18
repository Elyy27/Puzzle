#include<SDL.h>
#include<iostream>
#include<cstring>
#include<vector>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

const unsigned int SCREEN_WIDTH = 410;
const unsigned int SCREEN_HEIGHT = 600;

using namespace std;

void logSDLError(ostream& os, const string& msg, bool fatal = false);
void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
void quitSDL(SDL_Window*& window, SDL_Renderer*& renderer);