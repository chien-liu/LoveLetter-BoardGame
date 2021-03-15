#ifndef PLAYER_H
#define PLAYER_H
#include <assert.h>

#include <vector>

#include "card.h"
namespace loveletter {

struct PlayerAction {
  Card playCard;
  int playerId;
  Card guessCard;  // only for Guard(0)

  PlayerAction() : playCard(0), playerId(-1), guessCard(0) {}
};

class Player {
 public:
  bool isAlive;
  bool isSave;
  int id;

 protected:
  std::vector<Card> handCards;

 public:
  Player(int i) : isAlive(true), isSave(false), id(i){};
  void draw(Card card);
  std::vector<Card> getHandCard() const { return handCards; }
  void discard();
  virtual PlayerAction executeAction(std::vector<int> avail_playerId) = 0;
  void switchCard(Card card);
  virtual ~Player(){};

 protected:
  std::vector<int> getAvailCardId();
};

class AI : public Player {
 public:
  AI(int i): Player(i) {}
  PlayerAction executeAction(std::vector<int> avail_playerId) override;
};

class Human : public Player {
 public:
  Human(int i): Player(i) {}
  PlayerAction executeAction(std::vector<int> avail_playerId) override;

 private:
  bool leftOrRight();
};
}  // namespace loveletter
#endif