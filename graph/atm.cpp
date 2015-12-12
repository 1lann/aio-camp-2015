#include <vector>
#include <cstdio>
#include <set>
#include <stack>
#include <map>

// // TODO: Remove
// #include <fstream>

using namespace std;

#define NO_ID 511111

#define NO_PARENT 522222

#define NO_PUB_ACCESS 0
#define HAS_PUB_ACCESS 1

typedef struct localSystem {
	int money;
	set<int> systemConnections;
	int best;
	bool hasBest;
	bool hasAccessiblePub;
} localSystem;

typedef struct intersection {
	int parentCyclicSystem;
	int tarjanId;
	int resolvingParentId;
	int money;
	vector<int> connections;
	bool isPub;
} intersection;

map<int,intersection> intersections;
map<int,localSystem> abstractedSystems;
vector< pair<int,int> > systemConnectionResolver;
int tarjanIdCounter;
int cyclicSystemCounter;

set<int> notSeen;
stack<int> backtrack;

bool hasBeenSeen(int location) {
	if (notSeen.empty()) {
		return true;
	}

	return notSeen.find(location) == notSeen.end();
}

void findCyclicSystems(int location) {
	intersections[location].tarjanId =
		intersections[location].resolvingParentId = tarjanIdCounter++;

	notSeen.erase(notSeen.find(location));
	backtrack.push(location);

	for (int i = 0; i < (int)intersections[location].connections.size(); i++) {
		int neighbour = intersections[location].connections[i];

		if (!hasBeenSeen(neighbour)) {
			findCyclicSystems(neighbour);
		}

		if (intersections[neighbour].parentCyclicSystem == NO_PARENT) {
			intersections[location].resolvingParentId =
				min(intersections[location].resolvingParentId,
					intersections[neighbour].resolvingParentId);
		} else {
			systemConnectionResolver.push_back(make_pair(location,
				intersections[neighbour].parentCyclicSystem));
		}
	}

	if (intersections[location].tarjanId ==
			intersections[location].resolvingParentId) {
		int cur = -1;
		cyclicSystemCounter++;

		localSystem newSystem;
		newSystem.money = 0;
		newSystem.hasAccessiblePub = false;
		newSystem.best = 0;
		newSystem.hasBest = false;

		while (cur != location) {
			cur = backtrack.top();

			if (intersections[cur].isPub) {
				newSystem.hasAccessiblePub = true;
			}

			newSystem.money += intersections[cur].money;

			backtrack.pop();
			intersections[cur].parentCyclicSystem = cyclicSystemCounter;

			if (cur == location && backtrack.size() > 0) {
				int from = backtrack.top();
				systemConnectionResolver.push_back(make_pair(from, cyclicSystemCounter));
			}
		}

		abstractedSystems[cyclicSystemCounter] = newSystem;
	}
}

// Publess systems with no other connections have a value of 0.
int findBestRoute(int cyclicSystem) {
	if (abstractedSystems[cyclicSystem].hasBest) {
		return abstractedSystems[cyclicSystem].best;
	}

	if (abstractedSystems[cyclicSystem].systemConnections.empty() &&
		!abstractedSystems[cyclicSystem].hasAccessiblePub) {
		return 0;
	}

	int thisMoney = abstractedSystems[cyclicSystem].money;
	set<int> connections = abstractedSystems[cyclicSystem].systemConnections;

	int best = 0;

	set<int>::iterator it;
	for (it = connections.begin(); it != connections.end(); it++) {
		int externalSystem = *it;
		int externalRoute = findBestRoute(externalSystem);

		if (externalRoute == 0 && (!abstractedSystems[externalSystem].hasAccessiblePub) && (!abstractedSystems[cyclicSystem].hasAccessiblePub)) {

		} else {
			best = max(best, thisMoney + externalRoute);
		}
	}

	if (best == 0 && abstractedSystems[cyclicSystem].hasAccessiblePub) {
		best = thisMoney;
	}

	abstractedSystems[cyclicSystem].best = best;

	return best;
}

int main() {
	// TODO: Replace with cin
	// ifstream inputFile("atm.in");

	tarjanIdCounter = 0;
	cyclicSystemCounter = 0;

	int numIntersections;
	int numRoads;

	scanf("%d %d", &numIntersections, &numRoads);

	for (int i = 0; i < numRoads; i++) {
		int start;
		int end;

		scanf("%d %d", &start, &end);

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

		scanf("%d", &(thisIntersection.money));
		thisIntersection.parentCyclicSystem = NO_PARENT;
		thisIntersection.isPub = false;
		thisIntersection.tarjanId = NO_ID;
		thisIntersection.resolvingParentId = NO_ID;
		intersections[i] = thisIntersection;
	}

	int startingPosition;
	int numPubs;

	scanf("%d %d", &startingPosition, &numPubs);

	for (int i = 0; i < numPubs; i++) {
		int pubLocation;
		scanf("%d", &pubLocation);
		intersections[pubLocation].isPub = true;
	}

	findCyclicSystems(startingPosition);

	for (int i = 0; i < (int)systemConnectionResolver.size(); i++) {
		pair<int,int> connectionPair = systemConnectionResolver[i];
		int fromSystem = intersections[connectionPair.first].parentCyclicSystem;
		abstractedSystems[fromSystem].systemConnections.insert(connectionPair.second);
	}

	int startingCyclicSystem =
		intersections[startingPosition].parentCyclicSystem;

	printf("%d", findBestRoute(startingCyclicSystem));
}