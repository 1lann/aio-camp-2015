#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int numPeople;
int numKathryn;

// Kathryn's family. Age, then height.
vector<pair<int, int> > kathryn;
// Kathryn: oldest must be at the back (inverted age values)

vector<int> allPeople;

kathrynFamilyCache

typedef struct kathrynResult {
	int bestHeight;
	vector<pair<int, int> > kathryn; // Position, height
} kathrynResult;

int myAbs(int num) {
	if (num < 0) {
		return num * -1;
	}
	return num;
}

kathrynResult insertKathryn(int familyIndex, int startIndex) {
	pair<int, int> familyMember = kathryn[familyIndex];
	int heightBeforeMe = familyMember.second;

	if (familyIndex > 0) {
		heightBeforeMe = kathryn[familyIndex - 1].second;
	}

	kathrynResult bestResult;
	bestResult.bestHeight = 100000;
	int additionalHeight = 0;

	for (int i = startIndex; i < (numPeople - (numKathryn - familyIndex)); i++) {
		if (familyIndex == numKathryn - 1) {
			// Self tests only
		}

		if (i == startIndex) {
			kathrynResult thisResult = insertKathryn(familyIndex + 1, startIndex + 1);
			if (thisResult < bestResult.bestHeight) {
				bestResult = thisResult;
				additionalHeight = myAbs(familyMember.second - heightBeforeMe);
			}
		} else {
			// Account for the fact that the family member
			// before this one did not count the person behind
			// you currently.
			kathrynResult thisResult = insertKathryn(familyIndex + 1, startIndex + 1);
			if (thisResult < bestResult.bestHeight) {
				bestResult = thisResult;
				additionalHeight = myAbs(familyMember.second - allPeople[i]) + myAbs(familyMember.second - allPeople[i+1]);
			}
		}
	}
}

int main() {
	ifstream inputFile("congain.txt");
	inputFile >> numPeople >> numKathryn;

	for (int i = 0; i < numPeople; i++) {
		int height;
		inputFile >> height;

		if (i < numKathryn) {
			kathryn.push_back(i, height);
		} else {
			allPeople.push_back(i, height);
		}
	}

	sort(allPeople.begin(), allPeople.end());

	// Try inserting either by oldest to youngest
	int shortestHeightDiffA = 	
}