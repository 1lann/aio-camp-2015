#include <cstring>
#include <cstdio>
#include <queue>

#define HOLSTEINS 1
#define GUERNSEYS 2
#define JERSEYS 3

using namespace std;

typedef struct cows {
	int holsteins;
	int guernseys;
	int jerseys;
	bool hasValue;
} cow;

cows queries[17][100010];
int allCows[100010];
int numCows;
int maxLayer = 16;

// Inclusive bounds
pair<int,int> getBounds(int layer, int position) {
	int lower = ((1 << layer) * position) + 1;
	int upper = min(numCows, (1 << layer) + (lower - 1));
	return make_pair(lower, upper);
}

cows recursiveTreeSearch(int layer, int position) {
	// cout << "requested for layer " << layer << " and position " << position << endl;
	if (queries[layer][position].hasValue) {
		return queries[layer][position];
	}

	pair<int,int> bounds = getBounds(layer, position);

	if (bounds.first > bounds.second) {
		cows noCows;
		noCows.holsteins = 0;
		noCows.guernseys = 0;
		noCows.jerseys = 0;
		noCows.hasValue = true;
		queries[layer][position] = noCows;
		return noCows;
	}

	if (bounds.first == bounds.second) {
		int singleValue = allCows[bounds.first]; 

		cows thisNode;
		thisNode.holsteins = 0;
		thisNode.guernseys = 0;
		thisNode.jerseys = 0;

		if (singleValue == HOLSTEINS) {
			thisNode.holsteins = 1;
		} else if (singleValue == GUERNSEYS) {
			thisNode.guernseys = 1;
		} else if (singleValue == JERSEYS) {
			thisNode.jerseys = 1;
		}

		thisNode.hasValue = true;
		queries[layer][position] = thisNode;

		return thisNode;
	}

	cows left;

	if (queries[layer - 1][position * 2].hasValue) {
		left = queries[layer - 1][position * 2];
	} else {
		left = recursiveTreeSearch(layer - 1, position * 2);
	}

	cows right;

	if (queries[layer - 1][position * 2 + 1].hasValue) {
		right = queries[layer - 1][position * 2 + 1];
	} else {
		right = recursiveTreeSearch(layer - 1, position * 2 + 1);
	}

	cows thisNode;
	thisNode.holsteins = left.holsteins + right.holsteins;
	thisNode.guernseys = left.guernseys + right.guernseys;
	thisNode.jerseys = left.jerseys + right.jerseys;
	thisNode.hasValue = true;

	queries[layer][position] = thisNode;

	return thisNode;
}

cows executeQuery(int boundsStart, int boundsEnd) {
	cows sumCows;

	sumCows.holsteins = 0;
	sumCows.guernseys = 0;
	sumCows.jerseys = 0;

	queue<pair<int,int> > searchQueue;

	searchQueue.push(make_pair(maxLayer, 0));

	while (!searchQueue.empty()) {
		pair<int,int> searchRequest = searchQueue.front();
		searchQueue.pop();

		pair<int,int> bounds = getBounds(searchRequest.first, searchRequest.second);

		// cout << "layer " << searchRequest.first << " position " << searchRequest.second << endl;
		// cout << "bounds are " << bounds.first << " to " << bounds.second << endl;

		// Discard if out of bounds
		if (boundsStart > bounds.second || boundsEnd < bounds.first) {
			// cout << "discarded" << endl;
			continue;
		}

		if (boundsStart > bounds.first || boundsEnd < bounds.second) {
			// cout << "pushing it down" << endl;
			searchQueue.push(make_pair(searchRequest.first - 1, searchRequest.second * 2));
			searchQueue.push(make_pair(searchRequest.first - 1, searchRequest.second * 2 + 1));
			continue;
		}

		if (boundsStart <= bounds.second && boundsEnd >= bounds.first) {
			cows results = recursiveTreeSearch(searchRequest.first, searchRequest.second);
			sumCows.holsteins += results.holsteins;
			sumCows.guernseys += results.guernseys;
			sumCows.jerseys += results.jerseys;
		}
	}

	return sumCows;
}

int main() {
	FILE* inputFile = fopen("bcount.in", "r");

	memset(queries, 0, 17*100010*sizeof(cows));

	int numQueries;
	fscanf(inputFile, "%d %d", &numCows, &numQueries);

	for (int i = 1; i <= numCows; i++) {
		int thisCow;
		fscanf(inputFile, "%d", &thisCow);
		allCows[i] = thisCow;
	}

	FILE* outputFile = fopen("bcount.out", "w");

	for (int i = 0; i < numQueries; i++) {
		int boundsStart, boundsEnd;
		fscanf(inputFile, "%d %d", &boundsStart, &boundsEnd);
		cows result = executeQuery(boundsStart, boundsEnd);
		fprintf(outputFile, "%d %d %d\n", result.holsteins,
			result.guernseys, result.jerseys);
	}

	fclose(inputFile);
	fclose(outputFile);
}