#include <fstream>
#include <iostream>
#include <set>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

int tiles[210][210];
set< pair<int,int> > freeTiles;
vector< pair<int,int> > guards;
int height;
int width;

#define TILE_FREE 0
#define TILE_PIT 1
#define TILE_WALL 2

typedef struct weightedTile {
	int points;
	int row;
	int col;
} weightedTile;

bool cmpWeightedTile(weightedTile i, weightedTile j) {
	return i.points < j.points;
}

int getTilePoints(int row, int col) {
	int tilePoints = 0;
	if (row > 0) {
		if (tiles[row-1][col] != TILE_WALL) {
			tilePoints += 2;
		}
	} else {
		tilePoints++;
	}

	if (row < height-1) {
		if (tiles[row+1][col] != TILE_WALL) {
			tilePoints +=  2;
		}
	} else {
		tilePoints++;
	}

	if (col > 0) {
		if (tiles[row][col-1] != TILE_WALL) {
			tilePoints += 2;
		}
	} else {
		tilePoints++;
	}

	if (col < width-1) {
		if (tiles[row][col+1] != TILE_WALL) {
			tilePoints += 2;
		}
	} else {
		tilePoints++;
	}

	return tilePoints;
}

void placeGuard(int row, int col) {
	guards.push_back(make_pair(row, col));

	if (row > 0) {
		if (tiles[row - 1][col] != TILE_WALL) {
			for (int thisRow = row; thisRow >= 0; thisRow--) {
				tiles[thisRow][col] = TILE_PIT;				
			}
		}
	}

	if (row < height - 1) {
		if (tiles[row + 1][col] != TILE_WALL) {
			for (int thisRow = row; thisRow < height; thisRow++) {
				tiles[thisRow][col] = TILE_PIT;				
			}
		}
	}

	if (col > 0) {
		if (tiles[row][col - 1] != TILE_WALL) {
			for (int thisCol = col; thisCol >= 0; thisCol--) {
				tiles[row][thisCol] = TILE_PIT;				
			}
		}
	}

	if (col < width - 1) {
		if (tiles[row][col + 1] != TILE_WALL) {
			for (int thisCol = col; thisCol < width; thisCol++) {
				tiles[row][thisCol] = TILE_PIT;				
			}
		}
	}
}

int main() {
	ifstream inputFile("royalin.txt");

	inputFile >> height >> width;

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int tile;
			inputFile >> tile;
			tiles[row][col] = tile;
			if (tile == TILE_FREE) {
				freeTiles.insert(make_pair(row, col));
			}
		}
	}

	inputFile.close();

	vector<weightedTile> weightedTiles;

	set< pair<int,int> >::iterator it;
	for (it = freeTiles.begin(); it != freeTiles.end(); it++) {
		pair<int,int> freeTile = *it;
		weightedTile newWeighting;
		newWeighting.row = freeTile.first;
		newWeighting.col = freeTile.second;
		newWeighting.points = getTilePoints(freeTile.first, freeTile.second);

		weightedTiles.push_back(newWeighting);
	}

	sort(weightedTiles.begin(), weightedTiles.end(), cmpWeightedTile);

	for (int i = 0; i < (int)weightedTiles.size(); i++) {
		weightedTile tile = weightedTiles[i];
		if (tiles[tile.row][tile.col] == TILE_FREE) {
			placeGuard(tile.row, tile.col);
		}
	}

	ofstream outputFile("royalout.txt");

	outputFile << guards.size() << "\n";

	for (int i = 0; i < (int)guards.size(); i++) {
		outputFile << guards[i].first + 1 << " " << guards[i].second + 1 << "\n";
	}

	outputFile.close();

	return 0;
}