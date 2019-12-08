#import "stats.h"
#import <iostream>
#import <sstream>

#define MAXDRAW INT_MAX

Stats::Stats() {
	ttlBet = 0;
	ttlHand = 0;
	ttlReturn = 0;

	for (int i=0; i<MAXCOUNTRANGE; i++) {
		ttlHandCount[i] =0;
		ttlBetCount[i] = 0;
		ttlReturnCount[i] = 0;
		ttlPBJCount[i] = 0;
		ttlDBJCount[i] = 0;
		ttlEBJCount[i] = 0;
		ttlWINCount[i] = 0;
		ttlLOSCount[i] = 0;
		ttlEVNCount[i] = 0;
		ttlSURCount[i] = 0;
		ttlDBSCount[i] = 0;
		ttlPBSCount[i] = 0;
		ttlISOCount[i] = 0;
		ttlISXCount[i] = 0;
	}
}

unsigned int Stats::incHand(int count, bool breKO) {
	int ncount = 0;
	if (breKO) ncount = count + reKOCountOffset;
	if (ncount < 0) ncount = 0;
	else if (ncount >= MAXCOUNTRANGE) ncount = MAXCOUNTRANGE - 1;

	ttlHandCount[ncount]++;
	ttlHand++;
	return ttlHand;
}

unsigned int Stats::addBet(int bet, int count, bool breKO) {
	int ncount = 0;
	if (breKO) ncount = count + reKOCountOffset;
	if (ncount < 0) ncount = 0;
	else if (ncount >= MAXCOUNTRANGE) ncount = MAXCOUNTRANGE - 1;

	ttlBetCount[ncount] += bet;
	ttlBet += bet;
	return ttlBet;
}

unsigned int Stats::addReturn(int ret, int bet, int res, int count, bool breKO) {
	int ncount = 0;
	if (breKO) ncount = count + reKOCountOffset;
	if (ncount < 0) ncount = 0;
	else if (ncount >= MAXCOUNTRANGE) ncount = MAXCOUNTRANGE - 1;

	ttlReturnCount[ncount] += ret;
	ttlReturn += ret;
	seqReturn.push_back(ret - bet);

	switch (res) {
		case RESPBJ: ttlPBJCount[ncount]++; break;
		case RESDBJ: ttlDBJCount[ncount]++; break;
		case RESEBJ: ttlEBJCount[ncount]++; break;
		case RESWIN: ttlWINCount[ncount]++; break;
		case RESLOS: ttlLOSCount[ncount]++; break;
		case RESEVN: ttlEVNCount[ncount]++; break;
		case RESSUR: ttlSURCount[ncount]++; break;
		case RESDBS: ttlDBSCount[ncount]++; break;
		case RESPBS: ttlPBSCount[ncount]++; break;
		case RESISO: ttlISOCount[ncount]++; break;
		case RESISX: ttlISXCount[ncount]++; break;
	}

	return ttlReturn;
}

void Stats::initSequence() {
	ttlHandIn1Shuffle = 0;
	ttlReturnIn1Shuffle = 0;
	seqReturn.clear();
}

void Stats::recordDistribution(int shuffle_time) {
	#ifdef DEBUG
		std::cout << "Return_Sequence(" << shuffle_time << "): ";
		for (int i=0; i<seqReturn.size(); i++) std::cout << seqReturn.at(i) << ", ";
		std::cout << std::endl;
	#endif

	int resultChange = 0;
	int maxDraw = MAXDRAW;
	for (int i=0; i<seqReturn.size(); i++) {
		resultChange += seqReturn.at(i);
		if (maxDraw > resultChange) maxDraw = resultChange;
	}
	returnDistribution[maxDraw]++;
}

void Stats::show(bool breKO) {
	std::cout << "::Count, Return,     Hand,      Bet, Bet/Hand, ";
	std::cout << "PlayerBJ, DealerBJ,   EvenBJ,  PLY WIN, PLY LOSE, ";
	std::cout << "    EVEN,  SURRNDR,  DLR BST,  PLY BST, ";
	std::cout << "  INS OK, INS FAIL,  INS OK%";
	std::cout << std::endl;
	int countoffset = 0;
	if (breKO) countoffset = reKOCountOffset;

	for (int i=0; i<MAXCOUNTRANGE; i++) {
		std::cout.width(4); std::cout.fill(' ');
		std::cout << i - countoffset << ", ";

		if (ttlHandCount[i] > 0) {
			std::cout.width(8); std::cout.fill(' ');
			std::cout << (double)ttlReturnCount[i] / ttlBetCount[i] << ", ";
		} else {
			std::cout.width(8); std::cout.fill(' ');
			std::cout << 0 << ", ";
		}

		std::cout.width(8); std::cout.fill(' ');
		std::cout << ttlHandCount[i] << ", ";

		std::cout.width(8); std::cout.fill(' ');
		std::cout << ttlBetCount[i] << ", ";

		std::cout.width(8); std::cout.fill(' ');
		if (ttlHandCount[i] > 0) {
			std::cout << (double)ttlBetCount[i] / ttlHandCount[i] << ", ";
		} else std::cout << 0 << ", ";

		std::cout.width(8); std::cout.fill(' ');
		std::cout << ttlPBJCount[i] << ", ";
		
		std::cout.width(8); std::cout.fill(' ');
		std::cout << ttlDBJCount[i] << ", ";
		
		std::cout.width(8); std::cout.fill(' ');
		std::cout << ttlEBJCount[i] << ", ";
		
		std::cout.width(8); std::cout.fill(' ');
		std::cout << ttlWINCount[i] << ", ";
		
		std::cout.width(8); std::cout.fill(' ');
		std::cout << ttlLOSCount[i] << ", ";
		
		std::cout.width(8); std::cout.fill(' ');
		std::cout << ttlEVNCount[i] << ", ";
		
		std::cout.width(8); std::cout.fill(' ');
		std::cout << ttlSURCount[i] << ", ";

		std::cout.width(8); std::cout.fill(' ');
		std::cout << ttlDBSCount[i] << ", ";
		
		std::cout.width(8); std::cout.fill(' ');
		std::cout << ttlPBSCount[i] << ", ";
		
		std::cout.width(8); std::cout.fill(' ');
		std::cout << ttlISOCount[i] << ", ";
		
		std::cout.width(8); std::cout.fill(' ');
		std::cout << ttlISXCount[i] << ", ";

		std::cout.width(8); std::cout.fill(' ');
		std::cout << (double)ttlISOCount[i] / (ttlISOCount[i] + ttlISXCount[i]) << ", ";
		
		std::cout << std::endl;
	}

	std::cout << "::Max Draw in One Shuffle" << std::endl;
	std::map<int,int>::iterator it = returnDistribution.begin();
	while(it != returnDistribution.end()) {
		std::cout << "::Max Draw," << (*it).first << "," << (*it).second << std::endl;
		it++;
	}

	std::cout << "::Total Hand: " << ttlHand << std::endl;
	std::cout << "::Total Bet: " << ttlBet << std::endl;
	
	std::cout << "::Bet/Hand: " << (double)ttlBet / ttlHand << std::endl;
	std::cout << "::Return: " << (double)ttlReturn / ttlBet << std::endl;
}
