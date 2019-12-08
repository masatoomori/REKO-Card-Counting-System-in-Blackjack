#define NCARDS 52
#define NDECK 6

#import <iostream>
#import "shoe.h"

int main(){
	int numTest = 10000;
	int	hist[NDECK*NCARDS];
	for (int i=0; i<NDECK*NCARDS; i++) hist[i] = 0;

	for (int i=0; i<numTest; i++) {
		Shoe shoe(NDECK);
		while (shoe.size() > 0) {
			int card = shoe.pop_back();
			hist[shoe.size()] += card;
		}
	}

	for (int i=0; i<NDECK*NCARDS; i++) {
		std::cout << (double)hist[i] / numTest << std::endl;
	}

	return 0;
}
