#include "stopwatch.h"

stopwatch::stopwatch(const SDL_Rect& rect, const SDL_Color& color, TTF_Font* const font, const SDL_Color& fontColor)
	:interface(rect, color, font, fontColor),
	mStartTime(0), mElapsed("") {

}

void stopwatch::start() {
	time(&mStartTime);
}

void stopwatch::calculateTime(SDL_Renderer* const renderer) {
	time_t difference = time(NULL) - mStartTime;
	struct tm* timeinfo = gmtime(&difference);
	strftime(mElapsed, sizeof(mElapsed), "%H:%M:%S", timeinfo);

	loadTexture(renderer, mElapsed);
}