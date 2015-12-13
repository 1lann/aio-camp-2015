#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

map<string, int> palindromeChanges;

int leastChangesPlaindrome(string inputString) {
	if (palindromeChanges.find(inputString) != palindromeChanges.end()) {
		return palindromeChanges[inputString];
	}

	if (inputString.length() == 1) {
		palindromeChanges[inputString] = 0;
		return 0;
	}

	char front = *(inputString.begin());
	char end = *(inputString.end());

	if (front == end) {
		if (inputString.length() == 2) {
			palindromeChanges[inputString] = 0;
			return 0;
		}
		int result = leastChangesPlaindrome(inputString.substring(1, inputString.size() - 2))
		palindromeChanges[inputString] = result;
		return result;
	}

	if (inputString.length() == 2) {
		palindromeChanges[inputString] = 1;
		return 1;
	}

	return 
}

int main() {
	ifstream inputFile("palin.in");
	int inputLength;
	inputFile >> inputLength;

	string inputText = "";
	for (int i = 0; i < inputLength; i++) {
		char inputChar;
		inputFile >> inputChar;
		inputText.push_back(inputChar);
	}

	cout << inputText << endl;
}