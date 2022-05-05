#pragma once
#include "button.h"

class tile :public Button {
private:
	int mNumber;
public:
	tile(const SDL_Rect& rect, const SDL_Color& color, TTF_Font* const font, const SDL_Color& mFontColor, const int number);

	int getXPosition();
	int getYPosition();
	void setPositionTo(const int x, const int y);
	bool moveTo(const int x, const int y);
	int getNumber();
};
