#include <fstream>
#include <cstring>

using namespace std;

#define EMPTY_TILE 0
#define WALL_TILE 1

#define POSTER_LEFT_WALL_INDEX 1
#define POSTER_TOP_WALL_INDEX 2
#define POSTER_RIGHT_WALL_INDEX 3
#define POSTER_BOTTOM_WALL_INDEX 4

int height;
int width;

char floorPlan[1010][1010][5];

int posterPatternMatch(int row, int col) {
	if (row > 0 && col > 0) {
		char* A = floorPlan[row-1][col-1];
		char* B = floorPlan[row-1][col];
		char* C = floorPlan[row][col-1];
		char* D = floorPlan[row][col];

		if (A[0] == WALL_TILE && B[0] == WALL_TILE) {
			if (C[0] == EMPTY_TILE && D[0] == EMPTY_TILE) {
				if (C[POSTER_TOP_WALL_INDEX] == 0 && D[POSTER_TOP_WALL_INDEX] == 0) {
					floorPlan[row][col-1][POSTER_TOP_WALL_INDEX] = 1;
					floorPlan[row][col][POSTER_TOP_WALL_INDEX] = 1;
					return 1;
				}
				return 0;
			}
			return 0;
		}

		if (A[0] == WALL_TILE && C[0] == WALL_TILE) {
			if (B[0] == EMPTY_TILE && D[0] == EMPTY_TILE) {
				if (B[POSTER_LEFT_WALL_INDEX] == 0 && D[POSTER_LEFT_WALL_INDEX] == 0) {
					floorPlan[row-1][col][POSTER_LEFT_WALL_INDEX] = 1;
					floorPlan[row][col][POSTER_LEFT_WALL_INDEX] = 1;
					return 1;
				}
				return 0;
			}
			return 0;
		}

		if (C[0] == WALL_TILE && D[0] == WALL_TILE) {
			if (A[0] == EMPTY_TILE && B[0] == EMPTY_TILE) {
				if (A[POSTER_BOTTOM_WALL_INDEX] == 0 && B[POSTER_BOTTOM_WALL_INDEX] == 0) {
					floorPlan[row-1][col-1][POSTER_BOTTOM_WALL_INDEX] = 1;
					floorPlan[row-1][col][POSTER_BOTTOM_WALL_INDEX] = 1;
					return 1;
				}
				return 0;
			}
			return 0;
		}

		if (B[0] == WALL_TILE && D[0] == WALL_TILE) {
			if (A[0] == EMPTY_TILE && C[0] == EMPTY_TILE) {
				if (A[POSTER_RIGHT_WALL_INDEX] == 0 && C[POSTER_RIGHT_WALL_INDEX] == 0) {
					floorPlan[row-1][col-1][POSTER_RIGHT_WALL_INDEX] = 1;
					floorPlan[row][col-1][POSTER_RIGHT_WALL_INDEX] = 1;
					return 1;
				}
				return 0;
			}
			return 0;
		}
	}

	return 0;
}

int main() {
	ifstream inputFile("postin.txt");

	inputFile >> height >> width;

	memset(floorPlan, 0, 1010*1010*5*sizeof(char));

	int numPosters = 0;

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			char input;
			inputFile >> input;
			if (input == '.') {
				floorPlan[row][col][0] = EMPTY_TILE;				
			} else if (input == 'X') {
				floorPlan[row][col][0] = WALL_TILE;
			}
			numPosters += posterPatternMatch(row, col);
		}
	}

	inputFile.close();

	ofstream outputFile("postout.txt");
	outputFile << numPosters << '\n';
	outputFile.close();
}