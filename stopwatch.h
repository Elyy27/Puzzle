#pragma once
#include "interface.h"
#include <time.h>

class stopwatch :public interface {
private:
	time_t mStartTime;
	char mElapsed[80];

public:
	stopwatch(const SDL_Rect& rect, const SDL_Color& color, TTF_Font* const font, const SDL_Color& fontColor);

	void start();
	void calculateTime(SDL_Renderer* const renderer);
};

