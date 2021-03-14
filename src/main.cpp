#include <iostream>

#include "game.h"
#include <time.h>
#include <random>


int main(int argc, char *argv[]) {
  srand(time(NULL));

  loveletter::Game game(4);   // 4 players

  game.printStartMsg();

  while (!game.isEnd()) {
    game.drawCard();
    game.printPlayer();
    game.executeAction();
    game.update();
    game.checkEnd();
  }

  game.updateWinner();
  game.printEndMsg();
}