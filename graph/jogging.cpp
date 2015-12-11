#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

typedef struct road {
	unsigned short destination;
	short cost;
} road;

int maximumRun[1010];
map<int, vector<road> > roads;

int getMaximumRun(unsigned short landmark) {
	if (maximumRun[landmark] >= 0) {
		return maximumRun[landmark];
	}

	int maximum = 0;

	// Depth first search
	for (int i = 0; i < (int)roads[landmark].size(); i++) {
		int thisRunCost = getMaximumRun(roads[landmark][i].destination) +
			roads[landmark][i].cost;
		if (thisRunCost > maximum) {
			maximum = thisRunCost;
		}
	}

	maximumRun[landmark] = maximum;

	return maximum;
}
 
int main() {

	//
	// Data input
	//

	ifstream inputFile("jogin.txt");

	int numLandmarks;
	inputFile >> numLandmarks;

	for (;;) {
		unsigned short start;
		unsigned short end;
		short cost;
		inputFile >> start;
		inputFile >> end;
		inputFile >> cost;

		if (start == 0 && end == 0 && cost == 0) {
			break;
		}

		road thisRoad;
		thisRoad.destination = end;
		thisRoad.cost = cost;

		if (roads[start].size() == 0) {
			vector<road> newVector;
			roads[start] = newVector;
		}

		roads[start].push_back(thisRoad);
	}

	inputFile.close();

	for (int i = 0; i < 1010; i++) {
		maximumRun[i] = -1;
	}

	//
	// Processing
	//

	int maximum = 0;

	for (unsigned short i = 1; i <= numLandmarks; i++) {
		int thisRun = getMaximumRun(i);
		if (thisRun > maximum) {
			maximum = thisRun;
		}
	}

	//
	// Output
	//

	ofstream outputFile("jogout.txt");

	outputFile << maximum << '\n';

	outputFile.close();
}