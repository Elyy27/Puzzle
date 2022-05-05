#include "tile.h"

tile::tile(const SDL_Rect& rect, const SDL_Color& color, TTF_Font* const font, const SDL_Color& fontColor, const int number)
	: Button(rect, color, font, fontColor),
	mNumber(number) {

}

int tile::getXPosition() {
	return mRect.x;
}

int tile::getYPosition() {
	return mRect.y;
}

bool tile::moveTo(const int x, const int y) {
	if (mRect.x != x) {
		const int delta = (x - mRect.x > 0) ? 1 : -1;
		mRect.x += delta;
		mFontRect.x += delta;
		return false;
	}
	if (mRect.y != y) {
		const int delta = (y - mRect.y > 0) ? 1 : -1;
		mRect.y += delta;
		mFontRect.y += delta;
		return false;
	}
	return true;
}

void tile::setPositionTo(const int x, const int y) {
	mRect.x = x;
	mRect.y = y;

	centerText();
}

int tile::getNumber() {
	return mNumber;
}