#include <fstream>
#include <cstring>

using namespace std;

bool fences[101];

int main() {
	ifstream inputFile("paint.in");
	int aStart, aEnd, bStart, bEnd;

	inputFile >> aStart;
	inputFile >> aEnd;
	inputFile >> bStart;
	inputFile >> bEnd;

	inputFile.close();

	memset(fences, 0, sizeof(bool) * 101);

	for (int i = aStart; i < aEnd; i++) {
		fences[i] = true;
	}

	for (int i = bStart; i < bEnd; i++) {
		fences[i] = true;
	}

	int counter = 0;

	for (int i = 0; i <= 100; i++) {
		if (fences[i]) {
			counter++;
		}
	}

	ofstream outputFile("paint.out");
	outputFile << counter;
}