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
			tilePoints++;
		}
	}

	if (row < height-1) {
		if (tiles[row+1][col] != TILE_WALL) {
			tilePoints++;
		}
	}

	if (col > 0) {
		if (tiles[row][col-1] != TILE_WALL) {
			tilePoints++;
		}
	}

	if (col < width-1) {
		if (tiles[row][col+1] != TILE_WALL) {
			tilePoints++;
		}
	}

	return tilePoints;
}

void placeGuard(int row, int col) {
	guards.push_back(make_pair(row, col));

	queue< pair<int,int> > tileQueue;
	bool seen[210][210];

	memset(seen, 0, 210*210*sizeof(bool));

	tileQueue.push(make_pair(row, col));

	while (!tileQueue.empty()) {
		pair<int,int> nextTile = tileQueue.front();
		tileQueue.pop();

		seen[nextTile.first][nextTile.second] = true;

		if (nextTile.first > 0) {
			if (tiles[nextTile.first - 1][nextTile.second] != TILE_WALL &&
				!seen[nextTile.first - 1][nextTile.second]) {
				tiles[nextTile.first - 1][nextTile.second] = TILE_PIT;
				freeTiles.erase(make_pair(nextTile.first - 1, nextTile.second));
				tileQueue.push(make_pair(nextTile.first - 1, nextTile.second));
			}
		}

		if (nextTile.first < height - 1) {
			if (tiles[nextTile.first + 1][nextTile.second] != TILE_WALL &&
				!seen[nextTile.first + 1][nextTile.second]) {
				tiles[nextTile.first + 1][nextTile.second] = TILE_PIT;
				freeTiles.erase(make_pair(nextTile.first + 1, nextTile.second));
				tileQueue.push(make_pair(nextTile.first + 1, nextTile.second));
			}
		}

		if (nextTile.second > 0) {
			if (tiles[nextTile.first][nextTile.second - 1] != TILE_WALL &&
				!seen[nextTile.first][nextTile.second - 1]) {
				tiles[nextTile.first][nextTile.second - 1] = TILE_PIT;
				freeTiles.erase(make_pair(nextTile.first, nextTile.second - 1));
				tileQueue.push(make_pair(nextTile.first, nextTile.second - 1));
			}
		}

		if (nextTile.second < width - 1) {
			if (tiles[nextTile.first][nextTile.second + 1] != TILE_WALL &&
				!seen[nextTile.first][nextTile.second + 1]) {
				tiles[nextTile.first][nextTile.second + 1] = TILE_PIT;
				freeTiles.erase(make_pair(nextTile.first, nextTile.second + 1));
				tileQueue.push(make_pair(nextTile.first, nextTile.second + 1));
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