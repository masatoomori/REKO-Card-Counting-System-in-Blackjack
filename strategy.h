#ifndef ___STRATEGY_H___
#define ___STRATEGY_H___

#import <iostream>
#import <fstream>
#import <ctype.h>
#import <string>

class Strategy {
public:
	Strategy();
	int at(bool bSplit, int softScore, int hardScore, 
		int dealerTopCard, int stgcount, bool breKO, int indexcount);
	bool insurance(double count, bool breKO, int inscount);
	std::string name(int stg);
	void show(int stgNum);	//0: Basic Strategy 1: REKO
private:
	int bs[17+9+10][10];	//stgNum = 0
	int reko[17+9+10][10];	//stgNum = 1
};

#endif	//___STRATEGY_H___
