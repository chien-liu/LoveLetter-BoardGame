#ifndef LOVELETTER_H
#define LOVELETTER_H

#include <iostream>
#include <vector>

#include "card.h"
#include "player.h"

namespace loveletter {
class Game {
 public:
  Game(const int n_player);
  ~Game();
  void drawCard();
  void executeAction();
  void update();
  void checkEnd();
  void updateWinner();
  void printStartMsg() const;
  void printEndMsg() const;
  void printPlayer() const;
  bool isEnd() const { return end; }

 private:
  const int n_player;
  int round;
  bool end;
  CardPool pool;
  std::vector<Player*> players;
  int currentPlayerId;
  PlayerAction action;
  std::vector<int> winnerIds;

 private:
  void constructPlayers();
  void destructPlayers();
};
}  // namespace loveletter

#endif