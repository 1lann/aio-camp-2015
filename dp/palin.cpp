#include <fstream>
#include <cstring>

using namespace std;

char thisPalindrome[5010]; 

short leastChanges[5010][5010];

int leastChangesPlaindrome(int start, int end) {
	if (leastChanges[start][end] >= 0) {
		return (int)leastChanges[start][end];
	}

	if (start == end) {
		return 0;
	}

	if (thisPalindrome[start] == thisPalindrome[end]) {
		if (end - start == 1) {
			leastChanges[start][end] = 0;
			return 0;
		}

		int result = leastChangesPlaindrome(start + 1, end - 1);
		leastChanges[start][end] = result;
		return result;
	}

	if (end - start == 1) {
		return 1;
	}

	int result = min(leastChangesPlaindrome(start + 1, end),
		leastChangesPlaindrome(start, end - 1)) + 1;
	leastChanges[start][end] = result;
	return result;
}

int main() {
	memset(leastChanges, 0xffff, 510*510*sizeof(short));

	ifstream inputFile("palin.in");
	int inputLength;
	inputFile >> inputLength;

	for (int i = 0; i < inputLength; i++) {
		inputFile >> thisPalindrome[i];
	}

	inputFile.close();

	ofstream outputFile("palin.out");
	outputFile << leastChangesPlaindrome(0, inputLength - 1) << endl;
}