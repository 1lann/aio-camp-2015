#include <fstream>
#include <map>
#include <vector>

using namespace std;

map<vector<char>, int> palindromeChanges;

int leastChangesPlaindrome(vector<char> inputString, bool shouldCache) {
	if (palindromeChanges.find(inputString) != palindromeChanges.end()) {
		return palindromeChanges[inputString];
	}

	if (inputString.size() == 1) {
		return 0;
	}

	char front = *(inputString.begin());
	char end = *(inputString.end() - 1);

	if (front == end) {
		if (inputString.size() == 2) {
			return 0;
		}
		vector<char> newVector(inputString.begin() + 1, inputString.begin() + inputString.size() - 1);
		int result = leastChangesPlaindrome(newVector, !shouldCache);
		if (shouldCache) {
			palindromeChanges[inputString] = result;
		}
		return result;
	}

	if (inputString.size() == 2) {
		return 1;
	}

	vector<char> newVectorA(inputString.begin() + 1, inputString.begin() + inputString.size());
	vector<char> newVectorB(inputString.begin(), inputString.begin() + inputString.size() - 1);

	int result = min(leastChangesPlaindrome(newVectorA, !shouldCache),
		leastChangesPlaindrome(newVectorB, !shouldCache)) + 1;
	if (shouldCache) {
		palindromeChanges[inputString] = result;
	}
	return result;
}

int main() {
	ifstream inputFile("palin.in");
	int inputLength;
	inputFile >> inputLength;

	vector<char> inputText;
	for (int i = 0; i < inputLength; i++) {
		char inputChar;
		inputFile >> inputChar;
		inputText.push_back(inputChar);
	}

	inputFile.close();

	ofstream outputFile("palin.out");
	outputFile << leastChangesPlaindrome(inputText, false) << endl;
}