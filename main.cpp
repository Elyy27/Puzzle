#pragma warning(disable: 4996)
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

static bool isEmptyTileNeighbours(tileArray& tiles, const int row, const int col, tile* emptyTile) {
	static const int deltas[4][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} };

	for (int i = 0; i < 4; ++i) {
		if (inBounds(row + deltas[i][0], col + deltas[i][1], tiles.size() - 1, tiles[0].size() - 1)) {
			if (emptyTile == &tiles[row + deltas[i][0]][col + deltas[i][1]]) return true;
		}
	}
	return false;
}

unsigned int menu(SDL_Renderer* renderer, bool* exit, const unsigned int SCREEN_WIDTH, const unsigned int SCREEN_HEIGHT);


int main(int argc, char* argv[]) {
	//srand(time(0));
	SDL_Window* window;
	SDL_Renderer* renderer;
	initSDL(window, renderer);
	TTF_Init();
	SDL_Init(SDL_INIT_VIDEO);
	bool exit = false;
	unsigned int difficulty;
	while (1) {
		difficulty = menu(renderer, &exit, SCREEN_WIDTH, SCREEN_HEIGHT);
		if (exit) break;
	}
	SDL_Delay(10000);
	quitSDL(window, renderer);
	return 0;
}