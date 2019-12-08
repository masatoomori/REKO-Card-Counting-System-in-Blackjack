#define BASICSTG "BasicStrategy.csv"
#define REKOSTG "reKOStrategy.csv"
#define NOCOUNT 0
#define reKOCOUNT 1
#define HILOCOUNT 2
#define OFFSETSPLITSTG 25
#define OFFSETSOFTSTG 4
#define OFFSETHARDSTG -5
#define BURST 22

#import <fstream>
#import <iostream>
#import <ctype.h>
#import "strategy.h"

Strategy::Strategy(){
	char c;
	int playerIndex = 0;
	int dealerIndex = 0;

	std::ifstream bsfile(BASICSTG);
	while (bsfile.get(c)) {
		if (isdigit(c)) {
			bs[playerIndex][dealerIndex] = atoi(&c);
			dealerIndex++;
			if (dealerIndex == 10) { dealerIndex = 0; playerIndex++; }
		}
	}
	bsfile.close();

	playerIndex = 0;
	dealerIndex = 0;

	std::ifstream rekofile(REKOSTG);
	while (rekofile.get(c)) {
		if (isdigit(c)) {
			reko[playerIndex][dealerIndex] = atoi(&c);
			dealerIndex++;
			if (dealerIndex == 10) { dealerIndex = 0; playerIndex++; }
		}
	}
	rekofile.close();
}

int Strategy::at(bool bSplit, int softScore, int hardScore,
	int dealerTopCard, int stgcount, bool breKO, int indexcount){
	int dealerIndex;
	int playerIndex;
	if (dealerTopCard == 1) dealerIndex = 9;
	else dealerIndex = dealerTopCard - 2;

	if (bSplit) {
		playerIndex = hardScore / 2 + OFFSETSPLITSTG;
	} else if (softScore > hardScore && softScore < BURST) {
		playerIndex = softScore + OFFSETSOFTSTG;
	} else if (hardScore < BURST) {
		playerIndex = hardScore + OFFSETHARDSTG;
	} else return -1;

	#ifdef DEBUG
		std::cout << "(p,d) = (" << playerIndex
			<< "," << dealerIndex << ")" << std::endl;
	#endif

	if (breKO) {
		if (stgcount < indexcount) return bs[playerIndex][dealerIndex];
		else return reko[playerIndex][dealerIndex];
	} else return bs[playerIndex][dealerIndex];
}

bool Strategy::insurance(double count, bool breKO, int inscount){
	if (breKO) {
		if (count < inscount) return false;
		else return true;
	} else return false;
}

std::string Strategy::name(int stg) {
	switch (stg) {
		case 0: return "Stand";
		case 1: return "Hit";
		case 2: return "Double Down -> Stand";
		case 3: return "Double Down -> Hit";
		case 4: return "Surrender -> Stand";
		case 5: return "Surrender -> Hit";
		case 6: return "Split";
		default: return "";
	}
}

void Strategy::show(int stgNum){
	std::cout
		<< "0 : Stand" << std::endl
		<< "1 : Hit" << std::endl
		<< "2 : Double Down -> Stand" << std::endl
		<< "3 : Double Down -> Hit" << std::endl
		<< "4 : Surrender -> Stand" << std::endl
		<< "5 : Surrender -> Hit" << std::endl
		<< "6 : Split" << std::endl;

	for (int i=0; i<17+9+10; i++) {
		std::cout << i << ") ";
		for (int j=0; j<10; j++) {
			if (stgNum == NOCOUNT) std::cout << bs[i][j] << " ";
			if (stgNum == reKOCOUNT) std::cout << reko[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
