#ifndef ___SHOE_H___
#define ___SHOE_H___

#import <vector>

class Shoe {
public:
	Shoe(int nDeck);
	void init(int nDeck);
	int pop_back();
	void push_back(int cid);
	double penetration();
	void show();
	int size(){ return cards.size(); };
private:
	std::vector<int> cards;
	int maxCards;
};

#endif	//___SHOE_H___
