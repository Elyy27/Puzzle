#include "interface.h"

interface::interface(const SDL_Rect& rect, const SDL_Color& color, TTF_Font* const font, const SDL_Color& fontColor)
{
    mRect = rect;
    mColor = color;
    mFontRect = { 0, 0, 0, 0 };
    mFontColor = fontColor;
    mFont = font;
    mTexture = nullptr;
}
void interface::loadTexture(SDL_Renderer* const renderer, const char* text) {
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, text, mFontColor);
    if (textSurface == nullptr) logSDLError(cout, "Render Text Surface", true);
    else {
        mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (mTexture == nullptr) logSDLError(cout, "Create Texture Surface", true);
        else {
            mFontRect.w = textSurface->w;
            mFontRect.h = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }
    centerText();
}

void interface::centerText() {
    mFontRect.y = mRect.y + (mRect.h - mFontRect.h) * 0.5;
    mFontRect.x = mRect.x + (mRect.w - mFontRect.w) * 0.5;
}

void interface::render(SDL_Renderer* const renderer) const {
    SDL_SetRenderDrawColor(renderer, mColor.r, mColor.g, mColor.b, mColor.a);
    SDL_RenderFillRect(renderer, &mRect);

    if (mTexture != nullptr) SDL_RenderCopy(renderer, mTexture, nullptr, &mFontRect);
    else logSDLError(cout, "No Texture To Render", true);
}

void interface::free() {
    if (mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
    }
}