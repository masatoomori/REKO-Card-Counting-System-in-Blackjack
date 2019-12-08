#ifndef ___DEALER_H___
#define ___DEALER_H___

#import <vector>

class Dealer {
public:
	Dealer(bool hitSoft17);
	void draw(int cid);
	bool can_draw();
	bool open_card();
	bool is_blackjack() { return blackjack; }
	int front() { return cards.front(); }
	int back() { return cards.back(); }
	int get_score();
	int size() { return cards.size(); }
	int at(int pos) { return cards.at(pos); }
	void show_topCard();
	void show();
private:
	bool soft17hit;
	bool blackjack;
	int soft_score;
	int hard_score;
	int numberOfCardsVisible;
	std::vector<int> cards;
};

#endif	//___DEALER_H___
