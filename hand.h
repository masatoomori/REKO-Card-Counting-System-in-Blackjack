#ifndef ___HAND_H___
#define ___HAND_H___

#import <vector>

class Hand {
public:
	Hand(int chip);

	void activate() { active = true; }
	void set_drawable(int n) { numberOfCardsDrawable = n; }
	void hit(int cid);
	void doubledown(int cid);
	void surrender() { surrend = true; numberOfCardsDrawable = 0; }
	int split(int cid);

	bool is_active() { return active; }
	bool is_surrender() { return surrend; }
	bool is_blackjack() { return blackjack; }
	bool can_hit();
	bool can_split(int nHands, int maxhand);
	bool can_double();
	bool can_surrender(bool splited);

	int get_score(bool splited);
	int at(int pos) { return cards.at(pos); }
	int back() { return cards.back(); }
	int size() { return cards.size(); }
	int get_softScore() { return softScore; }
	int get_hardScore() { return hardScore; }
	int get_bet() { return bet; }
	void show(int h);
private:
	bool active;
	bool surrend;
	bool blackjack;
	int softScore;
	int hardScore;
	int bet;
	int numberOfCardsDrawable;
	std::vector<int> cards;
};

#endif	//___HAND_H___
