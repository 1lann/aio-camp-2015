#include <fstream>
#include <iostream>

#define NONE 4

using namespace std;

int cache[100][3][3][3][3];
char allCoal[100010];
int numShipments;

int getCoalProduced(int position, pair<char,char> lastA, pair<char,char> lastB) {
	if (cache[position % 2][lastA.first][lastA.second][lastB.first][lastB.second] > 0) {
		return cache[position % 2][lastA.first][lastA.second][lastB.first][lastB.second];
	}

	if (position >= numShipments) {
		return 0;
	}

	int thisProductionValue;
	if (lastA.first == lastA.second && lastA.first == allCoal[position]) {
		thisProductionValue = 1;
	} else if (lastA.first != lastA.second && lastA.first != allCoal[position] && lastA.second != allCoal[position]) {
		thisProductionValue = 3;
	} else {
		thisProductionValue = 2;
	}

	pair<char,char> nextA = make_pair(allCoal[position], lastA.first);
	pair<char,char> nextB = make_pair(allCoal[position], lastB.first);

	int nextAResult = getCoalProduced(position + 1, nextA, lastB);
	int nextBResult = getCoalProduced(position + 1, lastA, nextB); 

	if (nextAResult > nextBResult) {
		cout << "sending " << position << " to mine 1 from " << nextAResult << endl;
	} else {
		cout << "sending " << position << " to mine 2 from " << nextBResult << endl;
	}

	int maxResult = max(nextAResult, nextBResult) + thisProductionValue;

	cout << "for a result of " << maxResult << endl;

	cache[position % 2][lastA.first][lastA.second][lastB.first][lastB.second] = maxResult;
	return maxResult;
}

int main() {
	ifstream inputFile("miners.in");

	inputFile >> numShipments;

	for (int i = 0; i < numShipments; i++) {
		char inputChar;
		inputFile >> inputChar;
		if (inputChar == 'M') {
			allCoal[i] = 0;
		} else if (inputChar == 'B') {
			allCoal[i] = 1;
		} else if (inputChar == 'F') {
			allCoal[i] = 2;
		}
	}

	inputFile.close();

	ofstream outputFile("miners.out");

	outputFile << getCoalProduced(0, make_pair(NONE, NONE), make_pair(NONE, NONE));
}