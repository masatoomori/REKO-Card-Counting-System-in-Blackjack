#ifndef ___COUNTER_H___
#define ___COUNTER_H___

class Counter {
public:
	Counter(int nDeck);
	int reKOCount() { return nreKOCount; };
	int get_count(bool breKO);
	int BetFactor(bool breKO, int maxBetFactor);
	void count_card(int card, double penetration);
	void show();
private:
	int nreKOCount;
	int numDecks;
};

#endif	//___COUNTER_H___
