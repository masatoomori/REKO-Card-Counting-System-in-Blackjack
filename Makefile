CC	= g++ -O3
#CC	= g++ -DDEBUG

bj.bin: main.o shoe.o cid.o counter.o dealer.o hand.o strategy.o stats.o
	$(CC) -o bj.bin main.o shoe.o cid.o counter.o dealer.o hand.o strategy.o stats.o

main.o:		main.cc
	$(CC) -c main.cc
shoe.o:		shoe.cc
	$(CC) -c shoe.cc
cid.o:		cid.cc
	$(CC) -c cid.cc
counter.o:	counter.cc cid.cc
	$(CC) -c counter.cc cid.cc
dealer.o:	dealer.cc cid.cc
	$(CC) -c dealer.cc cid.cc
hand.o:		hand.cc
	$(CC) -c hand.cc
strategy.o:	strategy.cc
	$(CC) -c strategy.cc
stats.o: stats.cc
	$(CC) -c stats.cc

shoe.o:		shoe.h
cid.o:		cid.h
counter.o:	counter.h cid.h
dealer.o:	dealer.h cid.h
hand.o:		hand.h
strategy.o:	strategy.h
stats.o:	stats.h

clean:
	rm -f *.o
