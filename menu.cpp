#include "tile.h"
#include "stopwatch.h"

unsigned int menu(SDL_Renderer* renderer, bool* exit, const unsigned int SCREEN_WIDTH, const unsigned int SCREEN_HEIGHT) {
	const unsigned int NUMBER_OF_ROW_ELEMENTS = 1;
	const unsigned int NUMBER_OF_COL_ELEMENTS = 3;
	const unsigned int NUMBER_OF_ROW_BORDERS = NUMBER_OF_ROW_ELEMENTS + 1;
	const unsigned int NUMBER_OF_COL_BORDERS = NUMBER_OF_COL_ELEMENTS + 1;
	const unsigned int BORDER_THICKNESS = 20;

	const unsigned int BUTTON_WIDTH = SCREEN_WIDTH - 2 * BORDER_THICKNESS;
	const unsigned int BUTTON_HEIGHT = (SCREEN_HEIGHT - NUMBER_OF_COL_BORDERS * BORDER_THICKNESS) / NUMBER_OF_COL_ELEMENTS;

	const SDL_Color FONT_COLOR = { 0,0,0,255 }; //Black
	const SDL_Color BUTTON_COLOR = { 255, 182, 193, 255 }; //Pink
	const SDL_Color BUTTON_DOWN_COLOUR = { 135, 206, 250, 255 }; // Blue

	const int fontSize = BUTTON_HEIGHT - 40;
	TTF_Font* font = TTF_OpenFont("assets/octin sports free.ttf", fontSize);
	if (font == nullptr) logSDLError(cout, "Load Font", true);

	const char* buttonTexts[3] = { "3x3", "4x4", "5x5" };

	int startX = BORDER_THICKNESS;
	int startY = 0;

	vector<Button> buttons;
	for (int row = 0; row < NUMBER_OF_COL_ELEMENTS; ++row) {
		startY += BORDER_THICKNESS;
		SDL_Rect rect = { startX, startY, (int)BUTTON_WIDTH, (int)BUTTON_HEIGHT };
		Button button(rect, BUTTON_COLOR, font, FONT_COLOR);
		button.loadTexture(renderer, buttonTexts[row]);
		buttons.push_back(button);
		startY += BUTTON_HEIGHT;
	}

	const unsigned int FPS = 60;
	const float miliSecondsPerFrame = 1000 / FPS;
	float lastTimeRendered = SDL_GetTicks();
	float deltaTimeRendered;

	bool stop = false;
	SDL_Event event;
	unsigned int difficulty = 0;

	while (!stop) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				*exit = true;
				stop = true;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				for (int i = 0; i < NUMBER_OF_COL_ELEMENTS; ++i) {
					if (buttons[i].isMouseInside(x, y)) {
						buttons[i].changeColorTo(BUTTON_DOWN_COLOUR);
						difficulty = i + 3;
					}
				}
			}
			else if (event.type == SDL_MOUSEBUTTONUP) {
				for (auto& button : buttons) button.changeColorTo(BUTTON_COLOR);
				if (difficulty != 0) stop = true;
			}
		}

		deltaTimeRendered = SDL_GetTicks() - lastTimeRendered;
		if (deltaTimeRendered > miliSecondsPerFrame) {
			lastTimeRendered = SDL_GetTicks();
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			for (const auto& button : buttons) button.render(renderer);
			SDL_RenderPresent(renderer);
		}
		else SDL_Delay(miliSecondsPerFrame - deltaTimeRendered);
	}

	for (auto& button : buttons) button.free();

	TTF_CloseFont(font);
	font = nullptr;

	return difficulty;
}