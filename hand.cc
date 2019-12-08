#define BURST 22

#import "hand.h"
#import "cid.h"
#import <iostream>

Hand::Hand(int chip) {
	softScore = 0;
	hardScore = 0;
	bet = chip;
	numberOfCardsDrawable = BURST;
	active = false;
	surrend = false;
	blackjack = false;
}

void Hand::hit(int cid) {
	int num = cid2BJnum(cid);
	if (num == 1 && softScore + 11 < BURST) softScore += 11;
	else softScore += num;
	hardScore += num;
	cards.push_back(cid);
	numberOfCardsDrawable--;
}

void Hand::doubledown(int cid) {
	bet = bet * 2;
	int num = cid2BJnum(cid);
	if (num == 1 && softScore + 11 < BURST) softScore += 11;
	else softScore += num;
	hardScore += num;
	cards.push_back(cid);
	numberOfCardsDrawable = 0;
}

int Hand::split(int cid) {
	int cid1 = cards.at(0);
	int cid2 = cards.at(1);
	cards.clear(); softScore = 0; hardScore = 0;
	this->hit(cid1);
	this->hit(cid);
	if (cid2BJnum(cid1) == 1) numberOfCardsDrawable = 0;
	return cid2;
}

bool Hand::can_hit() {
	if (numberOfCardsDrawable <= 0) return false;
	if (softScore == 21) return false;
	if (hardScore >= 21) return false;
	return true;
}

bool Hand::can_split(int nHands, int maxhand) {
	if (nHands >= maxhand) return false;
	if (numberOfCardsDrawable <= 0) return false;
	if (cards.size() != 2) return false;
	if (cid2BJnum(cards.at(0)) != cid2BJnum(cards.at(1))) return false;
	return true;
}

bool Hand::can_double() {
	if (numberOfCardsDrawable <= 0) return false;
	if (cards.size() != 2) return false;
	return true;
}

bool Hand::can_surrender(bool splited) {
	if (cards.size() != 2) return false;
	if (splited) return false;
	return true;
}

int Hand::get_score(bool splited) {
	if (!splited && cards.size() == 2 && softScore == 21) blackjack = true;
	if (softScore >= BURST) return hardScore;
	if (softScore > hardScore) return softScore;
	return hardScore;
}

void Hand::show(int h) {
	std::cout << "player cards[" << h << "]: ";
	for (int i=0; i<cards.size(); i++) {
		std::cout << cid2SN(cards.at(i)) << " ";
	}
	std::cout << " : " << softScore << "/" << hardScore;
	std::cout << std::endl;
	//std::cout << "	active: ";
	//if (active) std::cout << "true" << std::endl;
	//else std::cout << "false" << std::endl;
	//std::cout << "	#drawable: " << numberOfCardsDrawable << std::endl;
}
