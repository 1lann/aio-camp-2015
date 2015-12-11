#include <vector>
#include <iostream>
#include <set>
#include <stack>
#include <map>

// TODO: Remove
#include <fstream>

using namespace std;

#define DEBUG 1

#define NO_ID 511111

#define NO_PARENT 522222

#define NO_PUB_ACCESS 0
#define HAS_PUB_ACCESS 1

typedef struct system {
	int money;
	set<int> systemConnections;
	int best;
	bool hasBest;
	bool hasAccessiblePub;
} system;

typedef struct intersection {
	int parentCyclicSystem;
	int tarjanId;
	int resolvingParentId;
	int money;
	vector<int> connections;
	bool isPub;
} intersection;

map<int,intersection> intersections;
map<int,system> abstractedSystems;
int tarjanIdCounter;
int cyclicSystemCounter;

set<int> notSeen;
stack<int> backtrack;

bool hasBeenSeen(int location) {
	return notSeen.find(location) == notSeen.end();
}

void findCyclicSystems(int location) {
	if (DEBUG) {
		cout << "Checking " << location << endl;
	}

	intersections[location].tarjanId =
		intersections[location].resolvingParentId = tarjanIdCounter++;
	if (DEBUG) {
		cout << location << " was automatically assigned ID: " << intersections[location].tarjanId << endl;
	}

	notSeen.erase(notSeen.find(location));
	backtrack.push(location);

	for (int i = 0; i < (int)intersections[location].connections.size(); i++) {
		int neighbour = intersections[location].connections[i];

		if (DEBUG) {
			cout << "Checking neighbour " << neighbour << endl;
		}

		if (!hasBeenSeen(neighbour)) {
			findCyclicSystems(neighbour);
		}

		if (intersections[neighbour].parentCyclicSystem == NO_PARENT) {
			intersections[location].resolvingParentId =
				min(intersections[location].resolvingParentId,
					intersections[neighbour].resolvingParentId);
			if (DEBUG) {
				cout << "Resolving parent id of " << location << " is now " << intersections[location].resolvingParentId << endl;
				if (intersections[neighbour].resolvingParentId == intersections[location].resolvingParentId) {
					cout << "As inherited from " << neighbour << endl;
				}
			}
		}
	}

	if (DEBUG) {
		cout << "Done checking neighbours for " << location << endl;
	}

	if (intersections[location].tarjanId ==
			intersections[location].resolvingParentId) {
		int cur = -1;
		cyclicSystemCounter++;

		if (DEBUG) {
			cout << "Found cyclic system, assigning id " <<
				cyclicSystemCounter << endl;
			cout << "Tarjan ID: " << intersections[location].tarjanId << endl;
		}
		
		system newSystem;
		newSystem.money = 0;
		newSystem.hasAccessiblePub = false;
		newSystem.best = 0;
		newSystem.hasBest = false;
 
		while (cur != location) {
			cur = backtrack.top();

			if (DEBUG) {
				cout << "Adding " << cur << " to system." << endl;
			}

			if (intersections[cur].isPub) {
				newSystem.hasAccessiblePub = true;
			}

			newSystem.money += intersections[cur].money;

			backtrack.pop();
			intersections[cur].parentCyclicSystem = cyclicSystemCounter;

			for (int i = 0; i < (int)intersections[cur].connections.size();
					i++) {
				intersection neighbour = intersections[cur].connections[i];
				if (neighbour.parentCyclicSystem != cyclicSystemCounter) {
					// Has an external connection
					newSystem.systemConnections.insert(
						neighbour.parentCyclicSystem);
				}
			}
		}
	}
}

// Publess systems with no other connections have a value of 0.
int findBestRoute(int startCyclicSystem) {
	if (abstractedSystems[startCyclicSystem].empty()) {
		return 0;
	}

	int thisMoney = abstractedSystems[startCyclicSystem].money;
	set<int> connections = abstractedSystems[startCyclicSystem].systemConnections;

	int best = thisMoney;

	set<int>::iterator it;
	for (it = connections.begin(); it != connections.end(); it++) {
		int externalSystem = *it;
		best = max(best, thisMoney + findBestRoute(externalSystem));
	}

	return best;
}

int main() {
	// TODO: Replace with cin
	ifstream inputFile("atm.in");

	tarjanIdCounter = 0;
	cyclicSystemCounter = 0;

	int numIntersections;
	int numRoads;

	inputFile >> numIntersections;
	inputFile >> numRoads;

	for (int i = 0; i < numRoads; i++) {
		int start;
		int end;

		inputFile >> start;
		inputFile >> end;

		intersection thisIntersection;

		if (intersections.find(start) != intersections.end()) {
			thisIntersection = intersections[start];
		}

		thisIntersection.connections.push_back(end);
		intersections[start] = thisIntersection;
	}

	for (int i = 1; i <= numIntersections; i++) {
		intersection thisIntersection;

		if (intersections.find(i) != intersections.end()) {
			thisIntersection = intersections[i];
		}

		notSeen.insert(i);

		inputFile >> thisIntersection.money;
		thisIntersection.parentCyclicSystem = NO_PARENT;
		thisIntersection.isPub = false;
		thisIntersection.tarjanId = NO_ID;
		thisIntersection.resolvingParentId = NO_ID;
		intersections[i] = thisIntersection;
	}

	int startingPosition;
	int numPubs;

	inputFile >> startingPosition;
	inputFile >> numPubs;

	for (int i = 0; i < numPubs; i++) {
		int pubLocation;
		inputFile >> pubLocation;
		intersections[pubLocation].isPub = true;
	}

	findCyclicSystems(startingPosition);

	cout << "-------------------------------" << endl;
	cout << "Starting finding best route..." << endl;
	cout << "-------------------------------" << endl;

	int startingCyclicSystem =
		intersections[startingPosition].parentCyclicSystem;


}