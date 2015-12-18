#include <fstream>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

#define NO_SWAP 1000000

char seen[100010];
map<int,char> seenB;
map<int,char> seenA;
int rowA[50010];
int rowB[50010];

map<pair<map<int,char>, map<int,char> >, int > cache;

vector<int> rowADoubles;
vector<int> rowBDoubles;

int width, day;

int attemptSwap(int i, int numSwap, map<int,char> seenInA, map<int,char> seenInB) {
	if (i >= width) {
		// Check validity
		map<int,char>::iterator it;
		for (it = seenA.begin(); it != seenA.end(); it++) {
			if ((it->second + seenInA[it->first]) >= 2) {
				return NO_SWAP;
			}
		}

		for (it = seenB.begin(); it != seenB.end(); it++) {
			if ((it->second + seenInB[it->first]) >= 2) {
				return NO_SWAP;
			}
		}

		return numSwap;
	}

	map< pair< map< int , char > , map< int , char > >, int >::iterator checkCache = cache.find(make_pair(seenInA, seenInB));
	if (checkCache != cache.end()) {
		cout << "used cache wow" << endl;
		return numSwap + checkCache->second;
	}

	// You need to make a choice.
	// Either to swap if you can, or not to swap.
	// But the question is: Does your choice make a difference?

	int bestSwap = NO_SWAP;

	// Only attempt the swap if it has semantic value
	if (seen[rowA[i]] > 1 || seen[rowB[i]] > 1) {
		map<int,char> seenInDiffA = seenInA;
		map<int,char> seenInDiffB = seenInB;

		seenInDiffA[rowA[i]]--;
		seenInDiffA[rowB[i]]++;
		seenInDiffB[rowB[i]]--;
		seenInDiffB[rowA[i]]++;

		int result = attemptSwap(i + 1, numSwap + 1, seenInDiffA, seenInDiffB);
		if (result < bestSwap) {
			bestSwap = result;
		}
	}

	int result = attemptSwap(i + 1, numSwap, seenInA, seenInB);
	if (result < bestSwap) {
		bestSwap = result;
	}

	if (bestSwap == NO_SWAP) {
		cache[make_pair(seenInA, seenInB)] = -1;
	} else {
		cache[make_pair(seenInA, seenInB)] = numSwap - bestSwap;
	}

	return bestSwap;
}


int main() {
	ifstream inputFile("plants.in");

	inputFile >> width >> day;

	for (int i = 0; i < width; i++) {
		int weed;
		inputFile >> weed;

		if (seen[weed] > 1) {
			inputFile.close();

			ofstream outputFile("plants.out");
			outputFile << "-1" << endl;
			outputFile.close();
			return 0;
		}

		seen[weed]++;
		seenA[weed]++;

		if (seenA[weed] == 2) {
			rowADoubles.push_back(weed);
		}

		rowA[i] = weed;
	}

	for (int i = 0; i < width; i++) {
		int weed;
		inputFile >> weed;

		if (seen[weed] > 1) {
			inputFile.close();

			ofstream outputFile("plants.out");
			outputFile << "-1" << endl;
			outputFile.close();
			return 0;
		}

		seen[weed]++;
		seenB[weed]++;

		if (seenB[weed] == 2) {
			rowBDoubles.push_back(weed);
		}

		rowB[i] = weed;
	}

	inputFile.close();

	if (day == 0) {
		// too ez 6 me
		int changes = max((int)rowBDoubles.size(), (int)rowADoubles.size());

		ofstream outputFile("plants.out");
		outputFile << changes << endl;
		outputFile.close();
	} else if (day == 1) {
		// go through each double, and try changing em'
		int changes = 0;

		map<int,char> empty;

		changes = attemptSwap(0, 0, empty, empty);

		if (changes >= NO_SWAP) {
			changes = -1;
		}
		
		ofstream outputFile("plants.out");
		outputFile << changes << endl;
		outputFile.close();
	}
	
}