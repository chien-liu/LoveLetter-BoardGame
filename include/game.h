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
  std::vector<Player*> players;
  int currentPlayerId;
  CardPool pool;
  PlayerAction action;
  int round;
  bool end;
  int winnerId;

 private:
  void constructPlayers();
  void destructPlayers();
};
}  // namespace loveletter

#endif