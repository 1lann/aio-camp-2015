#include <fstream>
#include <iostream>
#include <cstring>
#include <set>
#include <vector>

using namespace std;

typedef struct lightSwitch {
	short switchX;
	short switchY;
} lightSwitch;

typedef struct room {
	vector<lightSwitch> switches;
	bool isLit;
	bool visited;
} room;

int barnSize;
room barnMap[110][110];

set<room> unlitRooms;

int lightHerUp(int x, int y) {
	if (!barnMap[x][y].isLit) {
		return 0;
	}

	if (barnMap[x][y].visited) {
		return 0;
	}

	if (x != 1 || y != 1) {
		bool pass = false;
		// Check if is connected to visited system
		if (x > 1) {
			if (barnMap[x - 1][y].visited) {
				pass = true;
			}
		}

		if (x < barnSize) {
			if (barnMap[x + 1][y].visited) {
				pass = true;
			}
		} 

		if (y > 1) {
			if (barnMap[x][y - 1].visited) {
				pass = true;
			}
		}

		if (y < barnSize) {
			if (barnMap[x][y + 1].visited) {
				pass = true;
			}
		}

		if (!pass) {
			return 0;
		}
	}

	barnMap[x][y].visited = true;

	int lightsOn = 0;

	room thisRoom = barnMap[x][y];

	for (int i = 0; i < (int)thisRoom.switches.size(); i++) {
		lightSwitch thisSwitch = thisRoom.switches[i];

		if (!barnMap[thisSwitch.switchX][thisSwitch.switchY].isLit) {
			// Hit the switch!
			barnMap[thisSwitch.switchX][thisSwitch.switchY].isLit = true;
			lightsOn++;

			lightsOn += lightHerUp(thisSwitch.switchX, thisSwitch.switchY);
		}
	}

	if (x > 1) {
		lightsOn += lightHerUp(x - 1, y);
	}

	if (x < barnSize) {
		lightsOn += lightHerUp(x + 1, y);
	}

	if (y > 1) {
		lightsOn += lightHerUp(x, y - 1);
	}

	if (y < barnSize) {
		lightsOn += lightHerUp(x, y + 1);
	}

	return lightsOn;
}

int main() {
	ifstream inputFile("lightson.in");
	int numLines;
	inputFile >> barnSize >> numLines;

	memset(barnMap, 0, 110*110*sizeof(room));

	for (int i = 0; i < numLines; i++) {
		int x, y, a, b;
		inputFile >> x >> y >> a >> b;

		// Make switch room
		lightSwitch thisSwitch;
		thisSwitch.switchX = a;
		thisSwitch.switchY = b;

		barnMap[x][y].switches.push_back(thisSwitch);
	}

	barnMap[1][1].isLit = true;

	inputFile.close();

	ofstream outputFile("lightson.out");
	outputFile << lightHerUp(1, 1) + 1 << endl;
}