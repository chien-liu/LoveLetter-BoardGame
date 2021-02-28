# Simple Makefile

cc = g++
test_suffix = /usr/src/gtest/src/gtest_main.cc /usr/src/gtest/src/gtest-all.cc -I /usr/include -I /usr/src/gtest -L /usr/local/lib -lpthread

loveletter: main.o loveletter.o card.o player.o
	$(cc) -o loveletter main.o loveletter.o card.o player.o

main.o: main.cpp loveletter.h player.h card.h
	$(cc) -c main.cpp

loveletter.o: loveletter.cpp loveletter.h player.h card.h
	$(cc) -c loveletter.cpp

card.o: card.cpp card.h
	$(cc) -c card.cpp

player.o: player.cpp player.h
	$(cc) -c player.cpp

clean:
	rm *.o *.gch

test: unitTest.o loveletter.o card.o player.o
	$(cc) -o unitTest unitTest.o loveletter.o card.o player.o $(test_suffix)