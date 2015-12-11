#include <vector>
#include <iostream>
#include <set>
#include <stack>

using namespace std;

#define NO_ID -1

#define NO_PARENT -1

#define UNKNOWN_PUB_ACCESS 0
#define HAS_PUB_ACCESS 2
#define NO_PUB_ACCESS 1

typedef struct system {
	int money;
	vector<int> systemConnections;
	int hasAccessiblePub;
} system;

typedef struct intersection {
	int parentCyclicSystem;
	int tarjanId;
	int money;
	vector<int> connections;
	bool isPub;
} intersection;

map<int,intersection> intersections;
vector< vector<int> > cyclicSystems;
vector< vector<system> > abstractedSystems;
int tarjanIdCounter;

set<int> notSeen;
stack<int> backtrack;

bool hasBeenSeen(int location) {
	return notSeen.find(location) == notSeen.end()
}

void findCyclicSystems(int location) {
	intersection thisIntersection = intersections[location]; 
	intersections[location].tarjanId = tarjanIdCounter++;
	notSeen.erase(notSeen.find(location));
	backtrack.push(location);

	for (int i = 0; i < thisIntersection.connections.size(); i++) {
		
	}
}

int main() {
	// Intersections start from ONE: 1!!

	intersection placeholder;
	intersections.push_back(placeholder);

	int numIntersections;
	int numRoads;

	cin >> numIntersections;
	cin >> numRoads;

	for (int i = 0; i < numRoads; i++) {
		int start;
		int end;

		cin >> start;
		cin >> end

		intersection thisIntersection;

		if (intersections.find(i) != intersections.end()) {
			thisIntersection = intersections[i];
		}

		thisIntersection.connections.push_back(end);
		intersections[start] = thisIntersection;
	}

	for (int i = 0; i < numIntersections; i++) {
		intersection thisIntersection;

		if (intersections.find(i) != intersections.end()) {
			thisIntersection = intersections[i];
		}

		cin >> thisIntersection.money;
		thisIntersection.parentCyclicSystem = NO_PARENT;
		thisIntersection.isPub = false;
		thisIntersection.tarjanId = NO_ID;
		intersections.push_back(thisIntersection);
	}

	int startingPosition;
	int numPubs;

	cin >> startingPosition;
	cin >> numPubs;

	for (int i = 0; i < numPubs; i++) {
		int pubLocation;
		cin >> pubLocation;
		intersections[pubLocation].isPub = true;
	}
}