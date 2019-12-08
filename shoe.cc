#define NCARDS 52
#define NNUMBER 13

#import "shoe.h"
#import "cid.h"
#import "mt19937ar.c"
#import <iostream>

Shoe::Shoe(int nDeck){
	maxCards = nDeck * NCARDS;
	int count[NCARDS];
	for (int i=0; i<NCARDS; i++) count[i] = nDeck;

	for (int i=0; i<NCARDS*nDeck; i++) {
		while (true) {
			int cid = genrand_int32() % NCARDS;
			if (count[cid] > 0) {
				count[cid]--;
				cards.push_back(cid);
				break;
			}
		}
	}
}

void Shoe::init(int nDeck) {
	maxCards = nDeck * NCARDS;
	cards.clear();
	int count[NCARDS];
	for (int i=0; i<NCARDS; i++) count[i] = nDeck;

	for (int i=0; i<NCARDS*nDeck; i++) {
		while (true) {
			int cid = genrand_int32() % NCARDS;
			if (count[cid] > 0) {
				count[cid]--;
				cards.push_back(cid);
				break;
			}
		}
	}
}

int Shoe::pop_back() {
	int cid = cards.back();
	cards.pop_back();
	return cid;
}

void Shoe::push_back(int cid) {
	if (cid >= 0 && cid < NCARDS) cards.push_back(cid);
}

double Shoe::penetration() {
	return 1 - (double)cards.size() / maxCards;
}

void Shoe::show(){
	for (int i=0; i<cards.size(); i++) {
		int cid = cards.at(i);
		std::cout << i << ":" << cid2SN(cid) << " ";
		if (i % NNUMBER == NNUMBER - 1) std::cout << std::endl;
	}
	std::cout << std::endl;
}
