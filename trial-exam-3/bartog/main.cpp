#include <iostream>
#include <cstring>
#include <cstdlib>
#include "bartog.h"

using namespace std;

typedef struct node {
	int parent;
	bool children[2005];
} node;


int numNodes;
node allNodes[2005];
bool completedPairing[2005][2005];
int groupings[2005][2005];

void createPairing(int a, int b) {
	if ((!completedPairing[a][b]) && a != b) {
		// cout << "getting pairing between " << a << " and " << b << endl;
		int lca = getLCA(a, b);
		// cout << "it's " << lca << "!" << endl;
		if (lca == a) {
			allNodes[lca].children[b] = true;
			for (int i = 1; i < numNodes; i++) {
				if (allNodes[b].children[i]) {
					completedPairing[i][lca] = true;
					completedPairing[lca][i] = true;
				}
			}
		} else if (lca == b) {
			allNodes[lca].children[a] = true;
			for (int i = 1; i < numNodes; i++) {
				if (allNodes[a].children[i]) {
					completedPairing[i][lca] = true;
					completedPairing[lca][i] = true;
				}
			}
		} else {
			allNodes[lca].children[a] = true;
			allNodes[lca].children[b] = true;
			for (int i = 1; i < numNodes; i++) {
				if (allNodes[b].children[i]) {
					completedPairing[i][lca] = true;
					completedPairing[lca][i] = true;
				}
				if (allNodes[a].children[i]) {
					completedPairing[i][lca] = true;
					completedPairing[lca][i] = true;
				}
			}
		}

		completedPairing[a][b] = true;
		completedPairing[b][a] = true;
		completedPairing[lca][a] = true;
		completedPairing[a][lca] = true;
		completedPairing[b][lca] = true;
		completedPairing[lca][b] = true;

		// Fill the children of all the others!
		for (int i = 1; i <= numNodes; i++) {
			if (allNodes[i].children[lca]) {
				// I... I'll... never be your child... BAKA!
				completedPairing[a][i] = true;
				completedPairing[i][a] = true;
				completedPairing[i][b] = true;
				completedPairing[b][i] = true;
			}
		}
	}
}

int countChildren(int a) {
	int counter = 0;
	for (int i = 1; i <= numNodes; i++) {
		if (allNodes[a].children[i]) {
			counter++; 
		}
	}

	return counter;
}

int main() {
	numNodes = getN();
	srand(420);

	for (int i = 1; i <= (numNodes * 10); i++) {
		int a = rand() % numNodes + 1;
		int b = rand() % numNodes + 1;
		createPairing(a, b);
	}

	for (int i = 1; i <= numNodes; i++) {
		for (int j = 1; j <= numNodes; j++) {
			createPairing(i, j);
		}
	}

	int maxGroup = 0;

	// Scan through each person and group any people which have 2 children
	for (int i = 1; i <= numNodes; i++) {
		int numChildren = countChildren(i);
		groupings[numChildren / 2][0]++;
		int location = groupings[numChildren / 2][0];
		groupings[numChildren / 2][location] = i;
		maxGroup = max(maxGroup, numChildren / 2);
	}

	for (int group = 1; group <= maxGroup; group++) {
		int* thisGroup = groupings[group]; 

		for (int i = 1; i <= thisGroup[0]; i++) {
			int parentNode = thisGroup[i];
			for (int j = 1; j <= numNodes; j++) {
				if (allNodes[parentNode].children[j]) {
					if (allNodes[j].parent == 0) {
						allNodes[j].parent = parentNode;
					}
				}
			} 
		}

		group++;
	}

	int results[2005];

	for (int i = 0; i < numNodes; i++) {
		int parent = allNodes[i + 1].parent;
		if (parent == 0) {
			results[i] = i + 1;
		} else {
			results[i] = parent;
		}
	}

	finish(results);
}