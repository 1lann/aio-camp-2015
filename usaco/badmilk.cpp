#include <fstream>
#include <cstring>

using namespace std;

int milkBadness[55];
int personDrinkMilk[55][55];

int main() {
	ifstream inputFile("badmilk.in");

	int numPeople, numMilk, numDrink, numSick;
	inputFile >> numPeople >> numMilk >> numDrink >> numSick;

	memset(milkBadness, 0, 55*sizeof(int));
	memset(personDrinkMilk, 0, 55*55*sizeof(int));

	for (int i = 0; i < numDrink; i++) {
		int person, milk, atTime;

		inputFile >> person >> milk >> atTime;

		if (personDrinkMilk[person][milk] == 0 || personDrinkMilk[person][milk] > atTime) {
			personDrinkMilk[person][milk] = atTime;
		}
	}

	for (int i = 0; i < numSick; i++) {
		int person, atTime;
		inputFile >> person >> atTime;

		int* drinkProfile = personDrinkMilk[person];
		for (int milk = 1; milk <= numMilk; milk++) {
			if (drinkProfile[milk] < atTime && drinkProfile[milk] != 0) {
				// If milk was drunk by person earlier than they were sick
				milkBadness[milk]++;
			}
		}
	}

	inputFile.close();

	int worstMilk = 0;
	int worstBadness = 0;

	// Find the milk with the greatest milk badness
	for (int milk = 1; milk <= numMilk; milk++) {
		if (milkBadness[milk] > worstBadness) {
			worstMilk = milk;
			worstBadness = milkBadness[milk];
		}
	}

	int numSickPeople = 0;
	// Find people who drank that milk
	for (int person = 1; person <= numPeople; person++) {
		if (personDrinkMilk[person][worstMilk] > 0) {
			numSickPeople++;
		}
	}

	ofstream outputFile("badmilk.out");

	outputFile << numSickPeople;
}