#import <string>

#define NNUMBER 13
#define NSUIT 4

int cid2BJnum(int cid) {
	int num = cid % NNUMBER;
	if (num < 10) return (num + 1);
	else return 10;
}

std::string cid2SN(int cid) {
	std::string suit;
	if (cid < NNUMBER * 1) suit = 'S';
	else if (cid < NNUMBER * 2) suit = 'H';
	else if (cid < NNUMBER * 3) suit = 'D';
	else if (cid < NNUMBER * 4) suit = 'C';

	switch (cid % NNUMBER) {
		case 0: return suit + 'A';
		case 1: return suit + '2';
		case 2: return suit + '3';
		case 3: return suit + '4';
		case 4: return suit + '5';
		case 5: return suit + '6';
		case 6: return suit + '7';
		case 7: return suit + '8';
		case 8: return suit + '9';
		case 9: return suit + 'T';
		case 10: return suit + 'J';
		case 11: return suit + 'Q';
		case 12: return suit + 'K';
		default: return "";
	}
}
