#include<SDL.h>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<functional>
#include<vector>
#include<algorithm>
#include<sstream>
#include<fstream>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

const int SCREEN_HEIGHT = 410;
const int SCREEN_WIDTH = 600;

using namespace std;

void logSDLError(ostream& os, const string& msg, bool fatal = false);
void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
void quitSDL(SDL_Window*& window, SDL_Renderer*& renderer);