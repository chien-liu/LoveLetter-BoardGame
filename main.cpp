#include <iostream>

#include "loveletter.h"
#include <time.h>
#include <random>
using namespace std;

int main(int argc, char *argv[]) {
  srand(time(0));
  int n_player;
  if (argc > 1) {
    n_player = atoi(argv[1]);
  } else {
    n_player = 4;
  }

  LoveLetter game(n_player);

  game.printStartMsg();

  while (!game.end()) {
    game.drawCard();
    game.printPlayer();
    game.action();
    game.update();
    game.checkEnd();
  }

  game.updateWinner();
  game.printEndMsg();
}