LINK_TARGET = $(bin_dir)/LoveLetter-BoardGame


test_suffix = /usr/src/gtest/src/gtest_main.cc /usr/src/gtest/src/gtest-all.cc -I /usr/include -I /usr/src/gtest -L /usr/local/lib -lpthread

include_dir = include
object_dir = object
src_dir = src
bin_dir = bin
test_dir = unittest

vpath %.cpp src:unittest
vpath %.h include
vpath %.o object
vpath % bin:unittest

cc = g++
CCFLAG = -I$(include_dir)

$(LINK_TARGET): main.o card.o player.o game.o 
	$(cc) -o $@ $^

$(object_dir)/card.o: card.cpp
	$(cc) -c -o $@ $< $(CCFLAG)

$(object_dir)/player.o: player.cpp
	$(cc) -c -o $@ $< $(CCFLAG)

$(object_dir)/game.o: game.cpp
	$(cc) -c -o $@ $< $(CCFLAG)

$(object_dir)/main.o: main.cpp
	$(cc) -c -o $@ $< $(CCFLAG)

clean:
	rm object/*.o $(LINK_TARGET) $(test_dir)/testCard \
	   $(test_dir)/testPlayer $(test_dir)/testGame
	

test: testCard testPlayer testGame

$(test_dir)/testCard: testCard.cpp card.o
	$(cc) -o $@ $^ $(CCFLAG) $(test_suffix)
	
$(test_dir)/testPlayer: testPlayer.cpp player.o card.o
	$(cc) -o $@ $^ $(CCFLAG) $(test_suffix)

$(test_dir)/testGame: testGame.cpp player.o card.o game.o
	$(cc) -o $@ $^ $(CCFLAG) $(test_suffix)