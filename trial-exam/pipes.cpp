#include <fstream>
#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int connectors[11][2];
int numConnectors;
int width;
int height;

bool seen[5010][5010];

typedef struct pipe {
	int connections;
	int col;
	int row;
} pipe;

int absRow(int row) {
	if (row < 0) {
		return absRow(row + height);
	} else {
		return row % height;
	}
}
int absCol(int col) {
	if (col < 0) {
		return absCol(col + width);
	} else {
		return col % width;
	}
}

int main() {
	ifstream inputFile("pipesin.txt");

	inputFile >> width >> height;

	int houseCol;
	int houseRow;

	inputFile >> houseCol >> houseRow;

	inputFile >> numConnectors;

	for (int i = 0; i < numConnectors; i++) {
		int a;
		int b;
		inputFile >> connectors[i][0] >> connectors[i][1];
	}

	inputFile.close();

	memset(seen, 0, 5010*5010*sizeof(bool));

	pipe startPipe;
	startPipe.col = absCol(houseCol);
	startPipe.row = absRow(houseRow);
	startPipe.connections = 0;

	int shortest = -1;

	queue<pipe > searchQueue;

	searchQueue.push(startPipe);

	while (!searchQueue.empty()) {
		pipe thisPipe = searchQueue.front();

		if (thisPipe.row == 0 || thisPipe.col == 0) {
			shortest = thisPipe.connections; 
			break;
		}

		searchQueue.pop();

		for (int i = 0; i < numConnectors; i++) {
			int* thisConnector = connectors[i]; 

			int addRowA = absRow(thisConnector[0] + thisPipe.row);
			int subRowA = absRow(-thisConnector[0] + thisPipe.row);
			int addColA = absCol(thisConnector[1] + thisPipe.col);
			int subColA =  absCol(-thisConnector[1] + thisPipe.col);

			if (!seen[addRowA][addColA]) {
				seen[addRowA][addColA] = true;
				pipe newPipe;
				newPipe.row = addRowA;
				newPipe.col = addColA;
				newPipe.connections = thisPipe.connections + 1;
				searchQueue.push(newPipe);
			}
			if (!seen[addRowA][subColA]) {
				seen[addRowA][subColA] = true;
				pipe newPipe;
				newPipe.row = addRowA;
				newPipe.col = subColA;
				newPipe.connections = thisPipe.connections + 1;
				searchQueue.push(newPipe);
			}
			if (!seen[subRowA][addColA]) {
				seen[subRowA][addColA] = true;
				pipe newPipe;
				newPipe.row = subRowA;
				newPipe.col = addColA;
				newPipe.connections = thisPipe.connections + 1;
				searchQueue.push(newPipe);
			}
			if (!seen[subRowA][subColA]) {
				seen[subRowA][subColA] = true;
				pipe newPipe;
				newPipe.row = subRowA;
				newPipe.col = subColA;
				newPipe.connections = thisPipe.connections + 1;
				searchQueue.push(newPipe);
			}

			int addRowB = absRow(thisConnector[1] + thisPipe.row);
			int subRowB = absRow(-thisConnector[1] + thisPipe.row);
			int addColB = absCol(thisConnector[0] + thisPipe.col);
			int subColB =  absCol(-thisConnector[0] + thisPipe.col);

			if (!seen[addRowB][addColB]) {
				seen[addRowB][addColB] = true;
				pipe newPipe;
				newPipe.row = addRowB;
				newPipe.col = addColB;
				newPipe.connections = thisPipe.connections + 1;
				searchQueue.push(newPipe);
			}
			if (!seen[addRowB][subColB]) {
				seen[addRowB][subColB] = true;
				pipe newPipe;
				newPipe.row = addRowB;
				newPipe.col = subColB;
				newPipe.connections = thisPipe.connections + 1;
				searchQueue.push(newPipe);
			}
			if (!seen[subRowB][addColB]) {
				seen[subRowB][addColB] = true;
				pipe newPipe;
				newPipe.row = subRowB;
				newPipe.col = addColB;
				newPipe.connections = thisPipe.connections + 1;
				searchQueue.push(newPipe);
			}
			if (!seen[subRowB][subColB]) {
				seen[subRowB][subColB] = true;
				pipe newPipe;
				newPipe.row = subRowB;
				newPipe.col = subColB;
				newPipe.connections = thisPipe.connections + 1;
				searchQueue.push(newPipe);
			}
		}
	}

	ofstream outputFile("pipesout.txt");

	if (shortest >= 0) {
		outputFile << shortest << "\n";
	} else {
		outputFile << "No" << "\n";
	}

	outputFile.close();
}