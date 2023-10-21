#ifndef LOVELETTER_H
#define LOVELETTER_H

#include <iostream>
#include <vector>

#include "card.h"
#include "cardPile.h"
#include "player.h"
#include "playerGroup.h"

namespace loveletter {
class Game {
private:
  CardPile pile;
  PlayerGroup players;
  int currentRound = 1;

  AbstractPlayer *targetPlayer = nullptr;
  Card const *activateCardptr = nullptr;
  int assassinatedCardNumber = -1;

  std::vector<AbstractPlayer const *> checkWinner() const;

public:
  Game(const std::vector<std::string> &, int);
  ~Game();

  void drawCard();
  void playCard();
  void update();
  bool notEnd() const;

  friend void printStartMsg(const Game &);
  friend void printEndMsg(const Game &);
  friend void printPlayers(const Game &);
};

} // namespace loveletter
#endif