#ifndef ___STATS_H___
#define ___STATS_H___

#define MAXCOUNTRANGE 60

#define NOCOUNT 0
#define reKOCOUNT 1

#define RESPBJ 0
#define RESDBJ 1
#define RESEBJ 2
#define RESWIN 3
#define RESLOS 4
#define RESEVN 5
#define RESSUR 6
#define RESDBS 7
#define RESPBS 8
#define RESISO 9
#define RESISX 10

#import <vector>
#import <map>

static int reKOCountOffset = MAXCOUNTRANGE / 2;

class Stats {
public:
	Stats();
	unsigned int incHand(int count, bool breKO);
	unsigned int addBet(int bet, int count, bool breKO);
	unsigned int addReturn(int ret, int bet, int res, int count, bool breKO);

	void initSequence();
	void recordDistribution(int shuffle_time);
	void show(bool breKO);
private:
	unsigned int ttlHand;
	unsigned int ttlBet;
	unsigned int ttlReturn;

	std::map<int,int> returnDistribution;

	unsigned int ttlHandIn1Shuffle;
	unsigned int ttlReturnIn1Shuffle;
	std::vector<int> seqReturn;

	unsigned int ttlHandCount[MAXCOUNTRANGE];
	unsigned int ttlBetCount[MAXCOUNTRANGE];
	unsigned int ttlReturnCount[MAXCOUNTRANGE];

	unsigned int ttlPBJCount[MAXCOUNTRANGE];
	unsigned int ttlDBJCount[MAXCOUNTRANGE];
	unsigned int ttlEBJCount[MAXCOUNTRANGE];
	unsigned int ttlWINCount[MAXCOUNTRANGE];
	unsigned int ttlLOSCount[MAXCOUNTRANGE];
	unsigned int ttlEVNCount[MAXCOUNTRANGE];
	unsigned int ttlSURCount[MAXCOUNTRANGE];
	unsigned int ttlDBSCount[MAXCOUNTRANGE];
	unsigned int ttlPBSCount[MAXCOUNTRANGE];
	unsigned int ttlISOCount[MAXCOUNTRANGE];
	unsigned int ttlISXCount[MAXCOUNTRANGE];
};

#endif	//___STATS_H___
