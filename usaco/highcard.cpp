#include <fstream>
#include <cstdio>
#include <cstring>

using namespace std;

#define CARD_BESSIE 0
#define CARD_ELSIE 1
#define CARD_USED 2

int totalCards;
int failureHeight;
int lowestHeight;
char allCards[100010];

int bessiePlayHigher(int card) {
	int thisFailureHeight = min(failureHeight, totalCards);
	int startingPoint = max(card + 1, lowestHeight);

	for (int i = startingPoint; i <= thisFailureHeight; i++) {
		if (allCards[i] == CARD_BESSIE) {
			allCards[i] = CARD_USED;
			return 1;
		}
	}

	failureHeight = card;

	// Use lowest card

	for (int i = lowestHeight; i <= thisFailureHeight; i++) {
		if (allCards[i] == CARD_BESSIE) {
			lowestHeight = i + 1;
			allCards[i] = CARD_USED;
			return 0;
		}
	}

	return 0;
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

	failureHeight = totalCards;
	lowestHeight = 1;

	int bessiePoints = 0;

	for (int i = 0; i < numElsieCards; i++) {
		bessiePoints += bessiePlayHigher(elsiesCards[i]);
	}

	ofstream outputFile("highcard.out");
	outputFile << bessiePoints << endl;
}