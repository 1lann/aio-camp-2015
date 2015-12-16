#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>

using namespace std;

typedef struct Match {
	int startPos;
	int posFromZero;
	bool committed;
} Match;

int main() {
	char inputString[100010];
	scanf("%s", inputString);
	int inputLength = strlen(inputString);

	// Stores
	vector<Match> currentMatches;

	for (int i = 1; i < inputLength; i++) {
		for (int j = 0; j < (int)currentMatches.size(); j++) {
			Match thisMatch = currentMatches[j];
			if (thisMatch.committed) {
				int equivelantPosition = (i - thisMatch.startPos) % thisMatch.posFromZero; 
				
				// cout << "equivelant position " << equivelantPosition << " for " << thisMatch.startPos << endl;
				// cout << "input string " << i << ": " << inputString[i] << endl;

				if (inputString[equivelantPosition] != inputString[i]) {
					// Extend this string
					// cout << "string extended due to mismatch " << inputString[equivelantPosition] <<
					// 	" and " << inputString[i] << " to " << i + 1 << endl;
					// cout << "from " << currentMatches[j].posFromZero << endl;
					currentMatches[j].posFromZero = i + 1;
					currentMatches[j].startPos = 0;
				}
			} else {
				// cout << "checking " << thisMatch.startPos << endl;
				if (inputString[thisMatch.posFromZero + 1] == inputString[i]) {
					// cout << "matched " << thisMatch.posFromZero + 1 << " with " << i << " for " << thisMatch.startPos << endl;

					currentMatches[j].posFromZero++;

					if (currentMatches[j].posFromZero == currentMatches[j].startPos) {
						// cout << "matched start " << currentMatches[j].startPos << endl;
						// ooh a substring, commit it
						currentMatches[j].committed = true;
					}
				} else {
					// trash it
					currentMatches.erase(currentMatches.begin() + j);
					j--;
				}
			}
			
		}

		if (inputString[i] == inputString[0]) {
			Match match;
			match.startPos = i;
			match.posFromZero = 0;
			match.committed = false;
			currentMatches.push_back(match);
		}
	}

	int shortestSize = 100010;

	for (int i = 0; i < (int)currentMatches.size(); i++) {
		if (currentMatches[i].committed && (currentMatches[i].posFromZero < shortestSize)) {
			// cout << "taking from " << currentMatches[i].startPos << endl;
			shortestSize = currentMatches[i].posFromZero;
		}
	}

	if (shortestSize == 100010) {
		for (int i = 0; i < (int)currentMatches.size(); i++) {
			if (inputLength - (currentMatches[i].posFromZero + 1) < shortestSize) {
				shortestSize = inputLength - (currentMatches[i].posFromZero + 1);
			}
		}
	}

	if (shortestSize == 100010) {
		shortestSize = inputLength;
	}

	printf("%d\n", shortestSize);
}