#pragma once
#include "interface.h"
class Button : public interface 
{
public:
	Button(const SDL_Rect& rect, const SDL_Color& color, TTF_Font* const font, const SDL_Color& fontColor);

	bool isMouseInside(const int x, const int y) const;
	void changeColorTo(const SDL_Color& color);
};

