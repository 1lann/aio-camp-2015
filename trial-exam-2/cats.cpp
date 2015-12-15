#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <cstdlib>

using namespace std;

typedef struct CatPair {
	int first;
	int second;
	int value;

	bool operator<(CatPair a) const {
		return this->value < a.value; 
	}
} CatPair;

typedef struct CatPairNeg {
	int first;
	int second;
	int value;

	bool operator<(CatPairNeg a) const {
		return this->value > a.value; 
	}
} CatPairNeg;

int leftSide[100010];
int rightSide[100010];

CatPair makeCatPair(int first, int second) {
	CatPair thisPair;
	thisPair.first = first;
	thisPair.second = second;
	thisPair.value = leftSide[first] + rightSide[second];
	// cout << first << " --- " << second << " has value " << thisPair.value << endl;
	return thisPair;
}

CatPairNeg makeCatPairNeg(int first, int second) {
	CatPairNeg thisPair;
	thisPair.first = first;
	thisPair.second = second;
	thisPair.value = leftSide[first] + rightSide[second];
	return thisPair;
}

int getGreatest(int k, int numObjects) {
	int best;

	priority_queue<CatPair> choices;
	set<pair<int, int> > checkSet;
	choices.push(makeCatPair(0, 0));

	for (int i = 0; i < k; i++) {
		CatPair thisBestChoice = choices.top();
		choices.pop();

		if (thisBestChoice.first < numObjects - 1) {
			pair<int,int> testPair = make_pair(thisBestChoice.first + 1, thisBestChoice.second);
			if (checkSet.find(testPair) == checkSet.end()) {
				checkSet.insert(testPair);
				CatPair newCatPair = makeCatPair(thisBestChoice.first + 1, thisBestChoice.second);
				choices.push(newCatPair);
			}
		}

		if (thisBestChoice.second < numObjects - 1) {
			pair<int,int> testPair = make_pair(thisBestChoice.first, thisBestChoice.second + 1);
			if (checkSet.find(testPair) == checkSet.end()) {
				checkSet.insert(testPair);
				CatPair newCatPair = makeCatPair(thisBestChoice.first, thisBestChoice.second + 1);
				choices.push(newCatPair);
			}
		}

		best = thisBestChoice.value;

		// cout << currentSize << ": " << thisBestChoice.first << " --- "
		// 	<< thisBestChoice.second << endl;
	}

	return best;
}

int getLowest(int k, int numObjects) {
	int best; 

	priority_queue<CatPairNeg> choices;
	set<pair<int, int> > checkSet;
	choices.push(makeCatPairNeg(numObjects - 1, numObjects - 1));
	
	for (int i = 0; i < k; i++) {
		CatPairNeg thisBestChoice = choices.top();
		choices.pop();

		if (thisBestChoice.first > 0) {
			pair<int,int> testPair = make_pair(thisBestChoice.first - 1, thisBestChoice.second);
			if (checkSet.find(testPair) == checkSet.end()) {
				checkSet.insert(testPair);
				CatPairNeg newCatPairNeg = makeCatPairNeg(thisBestChoice.first - 1, thisBestChoice.second);
				choices.push(newCatPairNeg);
			}
		}

		if (thisBestChoice.second > 0) {
			pair<int,int> testPair = make_pair(thisBestChoice.first, thisBestChoice.second - 1);
			if (checkSet.find(testPair) == checkSet.end()) {
				checkSet.insert(testPair);
				CatPairNeg newCatPairNeg = makeCatPairNeg(thisBestChoice.first, thisBestChoice.second - 1);
				choices.push(newCatPairNeg);
			}
		}

		best = thisBestChoice.value;

		// cout << best << ": " << thisBestChoice.first << " --- "
		// 	<< thisBestChoice.second << endl;
	}

	return best;
}

int main() {
	FILE* inputFile = fopen("cats.in", "r");
	
	int numObjects;
	fscanf(inputFile, "%d", &numObjects);

	int k;
	fscanf(inputFile, "%d", &k);

	for (int i = 0; i < numObjects; i++) {
		fscanf(inputFile, "%d", &leftSide[i]);
	}

	for (int i = 0; i < numObjects; i++) {
		fscanf(inputFile, "%d", &rightSide[i]);
	}

	int currentSize;

	if (k < (numObjects * numObjects) / 2) {
		currentSize = getGreatest(k, numObjects);
	} else {
		currentSize = getLowest((numObjects * numObjects) - k + 1, numObjects);
	}

	ofstream outputFile("cats.out");
	outputFile << currentSize << endl;
}