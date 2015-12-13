#include <fstream>
// #include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

#define CARD_BESSIE 0
#define CARD_ELSIE 1
#define CARD_USED 2

int totalCards;
char allCards[100010];
vector<int> bessiesCards;

int bessiePlayHigher(int card) {
	// Card at the front is smallest, card at the back is highest.
	int nextCard = (int)bessiesCards.size() - 1;
	while (bessiesCards[nextCard] > card) {
		nextCard--;
	}

	if (nextCard < (int)bessiesCards.size() - 1) {
		// cout << "bessie played " << bessiesCards[nextCard + 1] << endl;
		// cout << "it's super effective!" << endl;
		bessiesCards.erase(bessiesCards.begin() + nextCard + 1);
		return 1;
	} else {
		// cout << "bessie played " << bessiesCards[0] << endl;
		// cout << "it's not very effective..." << endl;
		bessiesCards.erase(bessiesCards.begin());
		return 0;
	}
}

int main() {
	FILE* inputFile = fopen("highcard.in", "r");

	int numElsieCards;
	fscanf(inputFile, "%d", &numElsieCards);
	totalCards = numElsieCards * 2;

	int elsiesCards[numElsieCards];

	memset(allCards, CARD_BESSIE, 100010 * sizeof(char));

	for (int i = 0; i < numElsieCards; i++) {
		int thisCard;
		fscanf(inputFile, "%d", &thisCard);
		elsiesCards[i] = thisCard;
		allCards[thisCard] = CARD_ELSIE;
	}

	fclose(inputFile);

	for (int i = 1; i <= totalCards; i++) {
		if (allCards[i] == CARD_BESSIE) {
			bessiesCards.push_back(i);
		}
	}

	int bessiePoints = 0;

	for (int i = 0; i < numElsieCards; i++) {
		// cout << "elsie played " << elsiesCards[i] << endl;
		bessiePoints += bessiePlayHigher(elsiesCards[i]);
	}

	ofstream outputFile("highcard.out");
	outputFile << bessiePoints << endl;
}