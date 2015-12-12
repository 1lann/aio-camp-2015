#include <iostream>
#include <queue>
#include <vector>
#include "weigh.h"

using namespace std;

int numDiamonds;

pair<vector<int>,vector<int> > alternateSplitVector(vector<int> inputVector) {
	vector<int> vectorA;
	vector<int> vectorB;

	for (int i = 0; i < (int)inputVector.size(); i += 2) {
		vectorA.push_back(inputVector[i]);
		if (i + 1 < (int)inputVector.size()) {
			vectorB.push_back(inputVector[i+1]);
		}
	}

	return make_pair(vectorA, vectorB);
}


pair<vector<int>,vector<int> > initialFinder() {
	queue< pair< vector<int>,vector<int> > > finderQueue;

	vector<int> startingVectorA;
	vector<int> startingVectorB;

	for (int i = 1; i <= numDiamonds; i += 2) {
		startingVectorA.push_back(i);

		if (i + 1 <= numDiamonds) {
			startingVectorB.push_back(i + 1);
		}
	}

	finderQueue.push(make_pair(startingVectorA, startingVectorB));

	while (!finderQueue.empty()) {
		pair<vector<int>,vector<int> > testVectorPair = finderQueue.front();
		vector<int> testVector = testVectorPair.first;

		finderQueue.pop();

		int resultWeight = weight(testVector.size(), &(testVector[0]));
		if (resultWeight % 10 != 0) {
			// Found it!
			return testVectorPair;
		}

		// Split it up.
		finderQueue.push(alternateSplitVector(testVectorPair.first));
		finderQueue.push(alternateSplitVector(testVectorPair.second));
	}
}

pair<int,int> binarySearchDiamond(int start, int end, int* startArray) {
	if ((end - start) < 3) {
		int weightResult = weight(1, startArray + start);
		if (weightResult % 10 != 0) {
			return make_pair(startArray[start], weightResult);
		} 
		weightResult = weight(1, startArray + start + 1);
		if (weightResult % 10 != 0) {
			return make_pair(startArray[start + 1], weightResult);
		} 
		weightResult = weight(1, startArray + start + 2);
		if (weightResult % 10 != 0) {
			return make_pair(startArray[start + 2], weightResult);
		} 
	}

	int middle = (start + end) / 2;
	int weightResult = weight(middle - start, startArray + start);
	if (weightResult % 10 != 0) {
		// Recurse through first half non inclusive of middle
		return binarySearchDiamond(start, middle, startArray);
	} else {
		return binarySearchDiamond(middle, end, startArray);
	}
}

pair<int,int> recursiveFinder(pair<vector<int>,vector<int> > startVectorPair) {
	vector<int> first = startVectorPair.first;
	vector<int> second = startVectorPair.second;

	pair<int,int> firstPair = binarySearchDiamond(0, (int)first.size(), &(first[0]));
	pair<int,int> secondPair = binarySearchDiamond(0, (int)second.size(), &(second[0]));

	if (firstPair.second == 5) {
		return make_pair(firstPair.first, secondPair.first);
	} else {
		return make_pair(secondPair.first, firstPair.first);
	}
}

int main() {
	numDiamonds = getN();
	pair<vector<int>,vector<int> > resultPair = initialFinder();
	pair<int,int> results = recursiveFinder(resultPair);
	diamonds(results.first, results.second);
}