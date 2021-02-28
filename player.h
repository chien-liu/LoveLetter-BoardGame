#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"

struct Choice {
  Card card;
  int player_id;
  Card guess;
};

class Player {
 public:
  Player(bool ai);
  void draw(Card card);
  Choice chooseCard(std::vector<int> avail_card, std::vector<int> avail_player);
  Card showHand() { return this->hand; }
  Card showTmp() {return this->tmp_card; }
  bool oneCard() { return this->tmp_card == Card(0); }
  void discard() { hand = Card(0); }
  bool AI;
  bool alive;
  bool invincible;

 private:
  Card hand;
  Card tmp_card;
};

#endif