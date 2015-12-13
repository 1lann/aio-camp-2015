#include <fstream>

using namespace std;

int roadSpeedLimits[101];

int main() {
	ifstream inputFile("speeding.in");

	int numLimitSegments, numJourneySegments;

	inputFile >> numLimitSegments >> numJourneySegments;

	int curRoadPos = 0;

	for (int i = 0; i < numLimitSegments; i++) {
		int roadLength, speedLimit;
		inputFile >> roadLength >> speedLimit;

		for (int j = 0; j < roadLength; j++) {
			roadSpeedLimits[curRoadPos] = speedLimit;
			curRoadPos++;
		}
	}

	curRoadPos = 0;
	int speedOver = 0;

	for (int i = 0; i < numJourneySegments; i++) {
		int roadLength, travelSpeed;
		inputFile >> roadLength >> travelSpeed;
		for (int j = 0; j < roadLength; j++) {
			speedOver = max(speedOver, travelSpeed - roadSpeedLimits[curRoadPos]);
			curRoadPos++;
		}
	}

	inputFile.close();

	ofstream outputFile("speeding.out");
	outputFile << speedOver;
}