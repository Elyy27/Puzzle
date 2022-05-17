#include "tile.h"
#include "stopwatch.h"

typedef vector<vector<tile>> tileArray;

static void forEachTile(tileArray& tiles, function<void(tileArray&, const int, const int)>&& func) {
	for (int row = 0; row < tiles.size(); ++row) {
		for (int col = 0; col < tiles[row].size(); ++col) {
			func(tiles, row, col);
		}
	}
}

static inline bool inBounds(const int row, const int col, const int maxRow, const int maxCol) {
	return !(row<0 || row>maxRow || col<0 || col>maxCol);
}

static bool isEmptyTileInNeighbours(tileArray& tiles, const int row, const int col, tile* emptyTile) {
	static const int deltas[4][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} };

	for (int i = 0; i < 4; ++i) {
		if (inBounds(row + deltas[i][0], col + deltas[i][1], tiles.size() - 1, tiles[0].size() - 1)) {
			if (emptyTile == &tiles[row + deltas[i][0]][col + deltas[i][1]]) return true;
		}
	}
	return false;
}


void game(SDL_Renderer* renderer, bool* exit, const unsigned int DIFFICULTY, const unsigned int SCREEN_WIDTH, const unsigned int SCREEN_HEIGHT) {
	const unsigned int NUMBER_OF_ROW_ELEMENTS = DIFFICULTY;
	const unsigned int NUMBER_OF_COL_ELEMENTS = DIFFICULTY + 2;
	const unsigned int NUMBER_OF_ROW_BORDERS = NUMBER_OF_ROW_ELEMENTS + 1;
	const unsigned int NUMBER_OF_COL_BORDERS = NUMBER_OF_COL_ELEMENTS + 1;
	const unsigned int BORDER_THICKNESS = 6;
	const unsigned int TILE_WIDTH = (SCREEN_WIDTH - NUMBER_OF_ROW_BORDERS * BORDER_THICKNESS) / NUMBER_OF_ROW_ELEMENTS;
	const unsigned int TILE_HEIGHT = (SCREEN_HEIGHT - NUMBER_OF_COL_BORDERS * BORDER_THICKNESS) / NUMBER_OF_COL_ELEMENTS;

	const unsigned int STOPWATCH_WIDTH = SCREEN_WIDTH - 2 * BORDER_THICKNESS;
	const unsigned int STOPWATCH_HEIGHT = TILE_HEIGHT;

	const unsigned int BUTTON_WIDTH = SCREEN_WIDTH - 2 * BORDER_THICKNESS;
	const unsigned int BUTTON_HEIGHT = TILE_HEIGHT;

	const SDL_Color TILE_COLOR = { 255, 182, 193, 255 }; //Pink
	const SDL_Color TILE_COMPLETION_COLOR = { 135, 206, 250, 255 }; // Blue
	const SDL_Color EMPTY_TILE_COLOR = { 0, 0, 0, 255 }; // Black
	const SDL_Color FONT_COLOR = { 0, 0, 0, 255 }; // Black
	const SDL_Color STOPWATCH_COLOR = { 160, 102, 198, 255 }; // Purple
	const SDL_Color BUTTON_COLOR = { 255, 182, 193, 255 }; // Pink
	const SDL_Color BUTTON_DOWN_COLOR = { 135, 206, 250, 255 }; // Blue

	const int fontSize = TILE_HEIGHT - 40;
	TTF_Font* font = TTF_OpenFont("assets/octin sports free.ttf", fontSize);
	if (font == nullptr) logSDLError(cout, "Load Font", true);

	int startX = BORDER_THICKNESS;
	int startY = BORDER_THICKNESS;
	SDL_Rect rect = { startX, startY, (int)STOPWATCH_WIDTH, (int)STOPWATCH_HEIGHT };
	stopwatch stopwatch(rect, STOPWATCH_COLOR, font, FONT_COLOR);

	tileArray tiles;
	startY += TILE_HEIGHT;
	for (int row = 0; row < DIFFICULTY; ++row) {
		vector<tile> tileRow;
		startY += BORDER_THICKNESS;
		startX = 0;

		for (int col = 0; col < DIFFICULTY; ++col) {
			startX += BORDER_THICKNESS;
			rect = { startX, startY, (int)TILE_WIDTH, (int)TILE_HEIGHT };
			SDL_Color color;
			if (row == DIFFICULTY - 1 && col == DIFFICULTY - 1) color = EMPTY_TILE_COLOR;
			else color = TILE_COLOR;

			int number = row * DIFFICULTY + col + 1;

			tile tile(rect, color, font, FONT_COLOR, number);


			char numberStr[(((sizeof number) * CHAR_BIT) + 2) / 3 + 2];
			sprintf(numberStr, "%d", number);
			tile.loadTexture(renderer, numberStr);
			tileRow.push_back(tile);

			startX += TILE_WIDTH;
		}
		startY += TILE_HEIGHT;
		tiles.push_back(tileRow);
	}

	startX = BORDER_THICKNESS;
	startY += BORDER_THICKNESS;
	rect = { startX, startY, (int)BUTTON_WIDTH, (int)BUTTON_HEIGHT };
	Button menuButton(rect, BUTTON_COLOR, font, FONT_COLOR);
	menuButton.loadTexture(renderer, "Menu");

	const unsigned int FPS = 60;
	const float miliSecondsPerFrame = 1000 / FPS;
	float lastTimeRendered = SDL_GetTicks();
	float deltaTimeRendered;

	const unsigned int pixelsPerSecond = 500;
	const float miliSecondsPerPixel = 1000 / pixelsPerSecond;
	float lastTimeMoved;
	float deltaTimeMoved;

	tile* movingTile = nullptr;
	bool doneMoving = true;
	tile* emptyTile = &tiles[DIFFICULTY - 1][DIFFICULTY - 1];
	bool selected = false;
	int tempXPosition;
	int tempYPosition;

	const unsigned int TOTAL_SWAPS = 1000;

	int emptyTileRow = DIFFICULTY - 1;
	int emptyTileCol = DIFFICULTY - 1;

	vector<vector<int>> neighbours;

	//set random map
	srand(time(NULL));

	const int deltas[4][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} };

	for (int swap = 0; swap < TOTAL_SWAPS; ++swap) {
		for (int i = 0; i < 4; ++i) {
			const int deltaRow = deltas[i][0];
			const int deltaCol = deltas[i][1];
			if (inBounds(emptyTileRow + deltaRow, emptyTileCol + deltaCol, tiles.size() - 1, tiles[0].size() - 1)) {
				vector<int> neighbour = { emptyTileRow + deltaRow, emptyTileCol + deltaCol };
				neighbours.push_back(neighbour);
			}
		}

	//set random empty tile
		const int randomIndex = rand() % neighbours.size();
		const int row = neighbours[randomIndex][0];
		const int col = neighbours[randomIndex][1];

		//swap postions
		tempXPosition = emptyTile->getXPosition();
		tempYPosition = emptyTile->getYPosition();
		emptyTile->setPositionTo(tiles[row][col].getXPosition(), tiles[row][col].getYPosition());
		tiles[row][col].setPositionTo(tempXPosition, tempYPosition);

		//swap elements
		iter_swap(&tiles[row][col], emptyTile);
		emptyTile = &tiles[row][col];
		emptyTileRow = row;
		emptyTileCol = col;
		neighbours.clear();
	}

	bool stop = false;
	SDL_Event event;
	bool checkSolved = false;
	bool solved = false;
	bool menuButtonPressed = false;

	

	stopwatch.start();

	while (!stop) {
		while (SDL_PollEvent(&event) != 0) {

			if (event.type == SDL_QUIT) {
				stop = true;
				*exit = true;
			}

			if (doneMoving) {
				if (event.type == SDL_MOUSEBUTTONDOWN) {
					int x, y;
					SDL_GetMouseState(&x, &y);
					if (!solved) {
						forEachTile(tiles, [x, y, &movingTile, emptyTile, &selected, &doneMoving, &lastTimeMoved](tileArray& tiles, const int row, const int col) {
							if (tiles[row][col].isMouseInside(x, y)) {						
								if (isEmptyTileInNeighbours(tiles, row, col, emptyTile)) {
									Mix_Chunk* slideSound = Mix_LoadWAV("audio/slideSound.wav");
									Mix_PlayChannel(-1, slideSound, 0);
									movingTile = &tiles[row][col];
									selected = true;
									doneMoving = false;
									lastTimeMoved = SDL_GetTicks();
								}
							}
							});
					}
					if (menuButton.isMouseInside(x, y)) {
						menuButton.changeColorTo(BUTTON_DOWN_COLOR);
						Mix_Chunk* hitSound = Mix_LoadWAV("audio/hitSound.wav");
						Mix_PlayChannel(-1, hitSound, 0);
						menuButtonPressed = true;
					}
				}
				else if (event.type == SDL_MOUSEBUTTONUP) {
					menuButton.changeColorTo(BUTTON_COLOR);
					if (menuButtonPressed)
					{
						stop = true;
					}
				}
			}
		}
		if (selected && movingTile != nullptr) {
			tempXPosition = movingTile->getXPosition();
			tempYPosition = movingTile->getYPosition();
			selected = false;
		}

		if (movingTile != nullptr) {
			deltaTimeMoved = SDL_GetTicks() - lastTimeMoved;
			if (deltaTimeMoved > miliSecondsPerPixel) {
				int pixelsToMove = deltaTimeMoved / miliSecondsPerPixel;
				for (int i = 0; i < pixelsToMove; ++i) {
					doneMoving = movingTile->moveTo(emptyTile->getXPosition(), emptyTile->getYPosition());
					if (doneMoving) {
						emptyTile->setPositionTo(tempXPosition, tempYPosition);
						iter_swap(movingTile, emptyTile);
						emptyTile = movingTile;
						movingTile = nullptr;
						checkSolved = true;
						break;
					}
				}
				lastTimeMoved = SDL_GetTicks();
			}
		}

		if (checkSolved) {
			solved = true;
			forEachTile(tiles, [&solved, DIFFICULTY](tileArray& tiles, const int row, const int col) {
				const int number = row * DIFFICULTY + col + 1;
				if (tiles[row][col].getNumber() != number) solved = false;
				});
			checkSolved = false;
		}

		if (solved) {
			forEachTile(tiles, [emptyTile, &TILE_COMPLETION_COLOR](tileArray& tiles, const int row, const int col) {
				if (emptyTile != &tiles[row][col]) tiles[row][col].changeColorTo(TILE_COMPLETION_COLOR);
				});
		}
		else stopwatch.calculateTime(renderer);

		deltaTimeRendered = SDL_GetTicks(); -lastTimeRendered;
		if (deltaTimeRendered > miliSecondsPerFrame) {
			lastTimeRendered = SDL_GetTicks();

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			stopwatch.render(renderer);

			forEachTile(tiles, [renderer, emptyTile](tileArray& tiles, const int row, const int col) {
				if (emptyTile != &tiles[row][col]) tiles[row][col].render(renderer);
				});

			menuButton.render(renderer);

			SDL_RenderPresent(renderer);
		}
		else {
			SDL_Delay(miliSecondsPerFrame - deltaTimeRendered);
		}
	}
	if (solved)  cout << "Solved!" << endl;

	forEachTile(tiles, [](tileArray& tiles, const int row, const int col) {
		tiles[row][col].free();
		});

	stopwatch.free();

	TTF_CloseFont(font);
	font = nullptr;
	
}
