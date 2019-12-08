#define NOCOUNT 0
#define reKOCOUNT 1
#define HILOCOUNT 2

#import <iostream>
#import "counter.h"
#import "cid.h"

Counter::Counter(int nDeck){
	if (nDeck == 1) nreKOCount = -1;
	else if (nDeck == 2) nreKOCount = -5;
	else if (nDeck == 6) nreKOCount = -20;
	else if (nDeck == 8) nreKOCount = -28;
	else nreKOCount = (nDeck - 1) * (-4);
	numDecks = nDeck;
}

int Counter::BetFactor(bool breKO, int maxBetFactor){
	int betFactor = 1;
	if (breKO) {
		if (numDecks == 1) {
		} else if (numDecks == 2) {
		} else if (numDecks == 6) {
			/*if (nreKOCount > 3) betFactor = 8;
			else if (nreKOCount == 4) betFactor = 8;
			else if (nreKOCount == 3) betFactor = 8;
			else if (nreKOCount == 2) betFactor = 8;
			else if (nreKOCount == 1) betFactor = 4;
			else if (nreKOCount == 0) betFactor = 4;
			else if (nreKOCount == -1) betFactor = 4;
			else if (nreKOCount == -2) betFactor = 2;
			else if (nreKOCount == -3) betFactor = 2;
			else if (nreKOCount == -4) betFactor = 1;
			else if (nreKOCount == -5) betFactor = 1;*/
			if (nreKOCount > 3) betFactor = 15;
			else if (nreKOCount == 4) betFactor = 15;
			else if (nreKOCount == 3) betFactor = 10;
			else if (nreKOCount == 2) betFactor = 10;
			else if (nreKOCount == 1) betFactor = 5;
			else if (nreKOCount == 0) betFactor = 5;
			else if (nreKOCount == -1) betFactor = 5;
			else if (nreKOCount == -2) betFactor = 2;
			else if (nreKOCount == -3) betFactor = 2;
			else if (nreKOCount == -4) betFactor = 1;
			else if (nreKOCount == -5) betFactor = 1;
			else betFactor = 1;
		} else if (numDecks == 8) {
			if (nreKOCount > 5) betFactor = 20;
			else if (nreKOCount == 5) betFactor = 15;
			else if (nreKOCount == 4) betFactor = 15;
			else if (nreKOCount == 3) betFactor = 10;
			else if (nreKOCount == 2) betFactor = 10;
			else if (nreKOCount == 1) betFactor = 10;
			else if (nreKOCount == 0) betFactor = 5;
			else if (nreKOCount == -1) betFactor = 4;
			else if (nreKOCount == -2) betFactor = 3;
			else if (nreKOCount == -3) betFactor = 2;
			else if (nreKOCount == -4) betFactor = 1;
			else if (nreKOCount == -5) betFactor = 1;
			else betFactor = 1;
		}
	}
	if (betFactor > maxBetFactor) return maxBetFactor;
	else return betFactor;
}

void Counter::count_card(int card, double penetration){
	int num = cid2BJnum(card);
	if (num == 1) nreKOCount--;
	else if (num > 1 && num < 8) nreKOCount++;
	else if (num > 9) nreKOCount--;
}

int Counter::get_count(bool breKO){
	if (breKO) return nreKOCount;
	else return 0;
}

void Counter::show(){
	std::cout << "reKOCount:" << nreKOCount << " ";
}
