#include <fstream>
#include <set>
#include <iostream>
#include <vector>

using namespace std;

int changedIndex;
bool changed[7010];
int cached[101][10001];
int uncachedCalls;
int cachedCalls;

void uniqueIterative(vector<int> *plates, set<int> *storeSet, int value,
		int index) {
	if (index > changedIndex) {
		if (cached[index][0] > 0) {
			cachedCalls++;
			for (int i = 1; i < cached[index][0]; i++) {
				(*storeSet).insert(cached[index][i] + value);
			}
			return;
		}
	}

	uncachedCalls++;

	set<int> thisSet;

	for (int i = index; i < (int)((*plates).size()); i++) {
		thisSet.insert((*plates)[i]);
		uniqueIterative(plates, &thisSet, (*plates)[i], i + 1);
	}

	int counter = 1;

	for (set<int>::iterator it = thisSet.begin(); it != thisSet.end(); it++) {
		(*storeSet).insert(*it + value);
		cached[index][counter] = *it;
		counter++;
	}

	cached[index][0] = counter;
}

int main() {
	ifstream inputFile("nom.in");
	int numDishes;

	inputFile >> numDishes;

	vector<int> plates;
	for (int i = 0; i < numDishes; i++) {
		int inputPlate;
		inputFile >> inputPlate;

		plates.push_back(inputPlate);
	}

	inputFile.close();

	int mostUnique = 0;
	int changeFrom = 0;
	int changeTo = 0;

	for (int i = 0; i < numDishes; i++) {
		int previousValue = plates[i];
		changedIndex = i;

		if (!changed[previousValue]) {
			int lastUnique = 0;
			for (int w = 1; w <= 1000; w++) {
				plates[i] = w;

				set<int> uniqueSums;
				uniqueIterative(&plates, &uniqueSums, 0, 0);
				int numUnique = (int)uniqueSums.size();
				if (numUnique > mostUnique) {
					mostUnique = numUnique;
					changeFrom = previousValue;
					changeTo = w;
				}

				// if (numUnique < lastUnique) {
				// 	break;
				// }

				lastUnique = numUnique;
			}

			changed[previousValue] = true;
			plates[i] = previousValue;
		}
	}

	ofstream outputFile("nom.out");
	outputFile << changeFrom << " " << changeTo << endl;
	// cout << uncachedCalls << " uncached calls" << endl;
	// cout << cachedCalls << " cached calls" << endl;
}