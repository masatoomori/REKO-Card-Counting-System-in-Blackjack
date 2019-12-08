#define DEFAULTBET 10
#define MAXHAND 4
#define NOCOUNT 0
#define reKOCOUNT 1
#define BURST 22
#define INSreKO 3
#define INDEXreKO 3

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
#define RESOT0 90
#define RESOT1 91

#define MAXLOOP 1000

#import <iostream>
#import "counter.h"
#import "shoe.h"
#import "dealer.h"
#import "cid.h"
#import "hand.h"
#import "strategy.h"
#import "stats.h"

int main(int argc, char** argv){
	int shuffle_time = 1;
	double shufflePenetration = 0.8;
	int numDecks = 6;
	bool breKO = true;
	int maxBetFactor = 8;
	int inscount = 100;
	int indexcount = 100;
	bool hitSoft17 = true;

	if (argc > 1 && atoi(argv[1]) > 0) shuffle_time = atoi(argv[1]);
	if (argc > 2 && atoi(argv[2]) == 0) breKO = false;
	if (breKO) inscount = INSreKO;
	if (breKO) indexcount = INDEXreKO;
	if (argc > 3 && atoi(argv[3]) > 0) maxBetFactor = atoi(argv[3]);
	if (argc > 4 && atof(argv[4]) > 0 && atof(argv[4]) < 1) shufflePenetration = atof(argv[4]);
	if (argc > 5 && atoi(argv[5]) > 1) numDecks = atoi(argv[5]);
	if (argc > 6) inscount = atoi(argv[6]);
	if (argc > 7) indexcount = atoi(argv[7]);
	if (argc > 8 && atoi(argv[8]) == 0) hitSoft17 = false;

	Stats stats;
	Strategy stgtable;

	std::cout << std::endl;
	std::cout << "#Shuffle Time: " << shuffle_time << std::endl;
	if (breKO) std::cout << "#reKOCOUNT" << std::endl;
	else std::cout << "#NOCOUNT" << std::endl;
	std::cout << "#Max Bet Factor: " << maxBetFactor << std::endl;
	std::cout << "#penetration: " << shufflePenetration << std::endl;
	std::cout << "#nDeck: " << numDecks << std::endl;
	std::cout << "#ins: " << inscount << "+" << std::endl;
	std::cout << "#index: " << indexcount << "+" << std::endl;
	if (hitSoft17) std::cout << "#dealer hits soft 17" << std::endl;
	else std::cout << "#dealer does not hit soft 17" << std::endl;

	#ifdef DEBUG
		std::cout << "Basic Strategy" << std::endl;
		stgtable.show(NOCOUNT);
		std::cout << "reKO Strategy" << std::endl;
		stgtable.show(reKOCOUNT);
	#endif

	for (int i=0; i<shuffle_time; i++) {
		Counter counter(numDecks);
		Shoe shoe(numDecks);
		stats.initSequence();
		#ifdef DEBUG
			shoe.push_back(5);	//Player
			shoe.push_back(12);	//Player
			shoe.push_back(0);	//Player
			shoe.push_back(10);	//Dealer
			shoe.push_back(0);	//Dealer
			shoe.show();
		#endif

		int maxloop1 = 0;
		while (shoe.penetration() < shufflePenetration){
			if (maxloop1 > MAXLOOP) { std::cout << "loop overflow: 1" << std::endl; break; }
			else maxloop1++;
			#ifdef DEBUG
				std::cout << std::endl << std::endl;
				std::cout << "Penetration: " << shoe.penetration() << std::endl;
			#endif

			int betcount = counter.get_count(breKO);
			int bet = DEFAULTBET * counter.BetFactor(breKO, maxBetFactor);
			#ifdef DEBUG
				std::cout << "Bet: " << bet << std::endl;
				std::cout << std::endl;
			#endif

			//counter.show();
			Dealer dealer(hitSoft17);
			dealer.draw(shoe.pop_back());
			counter.count_card(dealer.back(), shoe.penetration());
			dealer.draw(shoe.pop_back());

			#ifdef DEBUG
				dealer.show_topCard();
				std::cout << "Count after dealer top card: ";
				counter.show();
				std::cout << std::endl;
				dealer.show();
			#endif

			Hand hand[MAXHAND] = {bet, bet, bet, bet};
			hand[0].activate();
			int stgcount = counter.get_count(breKO);
			stats.incHand(betcount, breKO);
			stats.addBet(bet, betcount, breKO);

			for (int h=0; h<MAXHAND; h++) {
				if (hand[h].is_active()) {
					int maxloop2 = 0;
					while (hand[h].size() < 2) {
						if (maxloop2 > MAXLOOP) { std::cout << "loop overflow: 1" << std::endl; break; }
						else maxloop2++;
						hand[h].hit(shoe.pop_back());
						counter.count_card(hand[h].back(), shoe.penetration());
					}

					#ifdef DEBUG
						std::cout << std::endl;
						std::cout << "Count after cards draw: ";
						counter.show();
						std::cout << std::endl;
						hand[h].show(h);
						std::cout << std::endl;
					#endif

					dealer.get_score();
					hand[h].get_score(hand[1].is_active());

					if (cid2BJnum(dealer.front()) == 1) {
						int stgcount = counter.get_count(breKO);
						#ifdef DEBUG
							dealer.show_topCard();
							counter.show();
						#endif
						if (stgtable.insurance(stgcount, breKO, inscount)) {
							#ifdef DEBUG
								std::cout << std::endl;
								std::cout << "take insurance" << std::endl;
							#endif
							stats.addBet(bet * 0.5, betcount, breKO);
							if (dealer.is_blackjack()) {
								stats.addReturn(bet * 1.5, bet, RESISO, betcount, breKO);
								break;
							} else stats.addReturn(bet * 0, bet, RESISX, betcount, breKO);
						}
					}

					if (dealer.is_blackjack() && !hand[h].is_blackjack()) break;

					int maxloop3 = 0;
					while (true) {
						if (maxloop3 > MAXLOOP) {
							std::cout << "loop overflow: 3" << std::endl;
							dealer.show_topCard();
							for (int h3=0; h3<MAXHAND; h3++) hand[h3].show(h3);
							break;
						} else maxloop3++;
						int handTopCard = cid2BJnum(hand[h].at(0));
						int softScore = hand[h].get_softScore();
						int hardScore = hand[h].get_hardScore();

						int nHands = 0;
						for (int h2=0; h2<MAXHAND; h2++) if (hand[h2].is_active()) nHands++;
						bool bSplit = hand[h].can_split(nHands, MAXHAND);
						int dealerTopCard = cid2BJnum(dealer.front());
						int stgcount = counter.get_count(breKO);
						int stg = stgtable.at(bSplit, softScore, hardScore, dealerTopCard, stgcount, breKO, indexcount);
						#ifdef DEBUG
							dealer.show_topCard();
							hand[h].show(h);
							std::cout << stgtable.name(stg) << std::endl;
						#endif
						if (stg == 0) break;	//stand
						else if (stg == 1) {	//hit
							if (hand[h].can_hit()) {
								hand[h].hit(shoe.pop_back());
								counter.count_card(hand[h].back(), shoe.penetration());
							} else break;
						} else if (stg == 2) {	//dd -> stand
							if (hand[h].can_double()) {
								hand[h].doubledown(shoe.pop_back());
								counter.count_card(hand[h].back(), shoe.penetration());
								stats.addBet(bet, betcount, breKO);
								break;
							} else break;
						} else if (stg == 3) {	//dd -> hit
							if (hand[h].can_double()) {
								hand[h].doubledown(shoe.pop_back());
								counter.count_card(hand[h].back(), shoe.penetration());
								stats.addBet(bet, betcount, breKO);
								break;
							} else if (hand[h].can_hit()) {
								hand[h].hit(shoe.pop_back());
								counter.count_card(hand[h].back(), shoe.penetration());
							} else break;
						} else if (stg == 4) {	//sur -> stand
							if (hand[h].can_surrender(hand[1].is_active())){
								hand[h].surrender();
								break;
							} else break;
						} else if (stg == 5) {	//sur -> hit
							if (hand[h].can_surrender(hand[1].is_active())){
								hand[h].surrender();
								break;
							} else if (hand[h].can_hit()) {
								hand[h].hit(shoe.pop_back());
								counter.count_card(hand[h].back(), shoe.penetration());
							} else break;
						} else if (stg == 6) {	//split -> stand
							for (int h2=h+1; h2<MAXHAND; h2++) {
								if (!hand[h2].is_active()) {
									hand[h2].activate();
									stats.addBet(bet, betcount, breKO);
									int cd = hand[h].split(shoe.pop_back());
									hand[h2].hit(cd);
									counter.count_card(cd, shoe.penetration());
									if (cid2BJnum(cd) == 1) hand[h2].set_drawable(1);
									break;
								}
							}
							if (nHands == MAXHAND) break;
						} else if (stg == 7) {	//split -> hit
							for (int h2=h+1; h2<MAXHAND; h2++) {
								if (!hand[h2].is_active()) {
									hand[h2].activate();
									stats.addBet(bet, betcount, breKO);
									int cd = hand[h].split(shoe.pop_back());
									hand[h2].hit(cd);
									counter.count_card(cd, shoe.penetration());
									if (cid2BJnum(cd) == 1) hand[h2].set_drawable(1);
									break;
								}
							}
							if (nHands == MAXHAND && hand[h].can_hit()) {
								hand[h].hit(shoe.pop_back());
								counter.count_card(hand[h].back(), shoe.penetration());
							} else break;
						} else break;
					}
				}				
				#ifdef DEBUG
					if (hand[h].is_active()) hand[h].show(h);
				#endif
			}

			counter.count_card(dealer.back(), shoe.penetration());
			int maxloop4 = 0;
			while (dealer.can_draw()) {
				if (maxloop4 > MAXLOOP) { std::cout << "loop overflow: 4" << std::endl; break; }
				else maxloop4++;
				dealer.draw(shoe.pop_back());
				counter.count_card(dealer.back(), shoe.penetration());
			}
			int dscr = dealer.get_score();

			#ifdef DEBUG
				std::cout << std::endl;
				std::cout << "Count after dealer draw" << std::endl;
				dealer.show();
				counter.show();
				std::cout << std::endl;
				dealer.show();
			#endif

			for (int h=0; h<MAXHAND; h++) {
				if (hand[h].is_active()) {
					int hscr = hand[h].get_score(hand[1].is_active());
					int bet = hand[h].get_bet();
					if (dealer.is_blackjack()) {
						if (hand[h].is_blackjack()) stats.addReturn(bet * 1, bet, RESEBJ, betcount, breKO);
						else stats.addReturn(bet * 0, bet, RESDBJ, betcount, breKO);
					} else if (hscr < BURST) {
						if (hand[h].is_surrender()) stats.addReturn(bet * 0.5, bet, RESSUR, betcount, breKO);
						else if (hand[h].is_blackjack()) stats.addReturn(bet * 2.5, bet, RESPBJ, betcount, breKO);
						else if (dscr >= BURST) stats.addReturn(bet * 2, bet, RESDBS, betcount, breKO);
						else if (dscr < hscr) stats.addReturn(bet * 2, bet, RESWIN, betcount, breKO);
						else if (dscr == hscr) stats.addReturn(bet * 1, bet, RESEVN, betcount, breKO);
						else stats.addReturn(bet * 0, bet, RESLOS, betcount, breKO);
					} else stats.addReturn(bet * 0, bet, RESPBS, betcount, breKO);
				}
			}
			#ifdef DEBUG
				stats.show(breKO);
			#endif
		}
		stats.recordDistribution(i);
	}

	stats.show(breKO);
	std::cout << "#Ret Param: " << shuffle_time
		<< " " << breKO
		<< " " << maxBetFactor
		<< " " << shufflePenetration
		<< " " << numDecks
		<< " " << inscount
		<< " " << indexcount
		<< " " << hitSoft17 << std::endl;
	return 0;
}
