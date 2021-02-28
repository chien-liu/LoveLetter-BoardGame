#ifndef LOVELETTER_H
#define LOVELETTER_H

#include <iostream>
#include <vector>

#include "card.h"
#include "player.h"


class LoveLetter {
 private:
  int n_player;
  std::vector<Player> players;
  int current_player;
  CardPool pool;
  Choice choice;
  int round;
  bool terminate;
  int winner;

 public:
  LoveLetter(int n_player);
  void drawCard();
  void action();
  void update();
  void checkEnd();
  void updateWinner();
  void printStartMsg() {
    std::cout << "[Loveletter]\n" << n_player << "players" << std::endl;
  }
  void printEndMsg() {
    std::cout << "Game end\n"
              << "Player" << winner << " wins" << std::endl;
  }
  void printPlayer();
  bool end() { return this->terminate; }
};

#endif