#ifndef INTERFACE_H
#define INTERFACE_H


#include "basement.h"

class interface {
protected:
	SDL_Rect mRect;
	SDL_Color mColor;

	TTF_Font* mFont;
	SDL_Rect mFontRect;
	SDL_Color mFontColor;
	SDL_Texture* mTexture;

	void centerText();

public:
	interface(const SDL_Rect& rect, const SDL_Color& color, TTF_Font* const font, const SDL_Color& fontColor);
	
	void loadTexture(SDL_Renderer* const renderer, const char* text);
	void render(SDL_Renderer* const renderer) const;
	void free();
};

#endif // !INTERFACE_H