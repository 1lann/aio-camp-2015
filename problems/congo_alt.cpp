#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int numPeople;
int numKathryn;

// Position, height
vector<pair<int, int> > allPeople;
vector<pair<int, int> > tallerThanKath;
vector<pair<int, int> > shorterThanKath;

int main() {
	ifstream inputFile("congain.txt");
	inputFile >> numPeople >> numKathryn;

	int tallestKath = 0;
	int shortestKath = 1000000;

	for (int i = 0; i < numPeople; i++) {
		int height;
		inputFile >> height;

		if (i < numKathryn) {
			allPeople.push_back(i, height);
		} else {
			allPeople.push_back(i, height);
		}
	}

	sort(allPeople.begin(), allPeople.end());

	// Try inserting either by oldest to youngest
	int shortestHeightDiffA = 	
}