#define BURST 22

#import "dealer.h"
#import "cid.h"
#import <iostream>

Dealer::Dealer(bool hitSoft17) {
	soft17hit = hitSoft17;
	blackjack = false;
	soft_score = 0;
	hard_score = 0;
	numberOfCardsVisible = 1;
}

void Dealer::draw(int cid) {
	int num = cid2BJnum(cid);
	if (num == 1 && soft_score + 11 < BURST) soft_score += 11;
	else soft_score += num;
	hard_score += num;
	cards.push_back(cid);
}

bool Dealer::can_draw() {
	if (!soft17hit && soft_score == 17) return false;
	if (soft_score >= 18 && soft_score < BURST) return false;
	if (hard_score >= 17) return false;
	return true;
}

bool Dealer::open_card() {
	if (numberOfCardsVisible < cards.size()) numberOfCardsVisible++;
	else return false;

	std::cout << "dealer cards: ";
	for (int i=0; i<numberOfCardsVisible; i++) {
		std::cout << cid2SN(cards.at(i)) << " ";
	}
	std::cout << std::endl;
	return true;
}

int Dealer::get_score() {
	if (cards.size() == 2 && soft_score == 21) blackjack = true;
	if (soft_score >= BURST) return hard_score;
	if (soft_score > hard_score) return soft_score;
	return hard_score;
}

void Dealer::show_topCard(){
	std::cout << "dealer top card: "
		<< cid2SN(cards.front()) << std::endl;
}

void Dealer::show() {
	std::cout << "dealer cards: ";
	for (int i=0; i<cards.size(); i++) {
		std::cout << cid2SN(cards.at(i)) << " ";
	}
	std::cout << " : " << soft_score << "/" << hard_score;
	std::cout << std::endl;
	
}
