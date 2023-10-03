#include "player.h"

#include <stdio.h>
#include <unistd.h>

#include <algorithm>
#include <iostream>
#include <random>

#include "card.h"

namespace loveletter
{
  // AbstractPlayer
  AbstractPlayer::AbstractPlayer(const std::string &s) : name(s) {}
  AbstractPlayer::~AbstractPlayer() {}
  void AbstractPlayer::drawCard(Card *const cptr)
  {
    hand.push_back(cptr);
  }

  // AI
  AI::AI(const std::string &s) : AbstractPlayer(s) {}
  AI::~AI() {}
  Card const *AI::playCard()
  {
    if (hand.size() != 2)
      throw std::runtime_error("Invalid size of hand");
    // std::random_shuffle(hand.begin(), hand.end());
    Card const *output = hand.back();
    hand.pop_back();
    return output;
  }
  // const std::string &choosePlayer(std::vector<std::string &>) override;
  // int chooseCardId() override;

  // Human
  Human::Human(const std::string &s) : AbstractPlayer(s) {}
  Human::~Human() {}
  Card const *Human::playCard()
  {
    if (hand.size() != 2)
      throw std::runtime_error("Invalid size of hand");
    return hand[0];
  }

} // namespace loveletter