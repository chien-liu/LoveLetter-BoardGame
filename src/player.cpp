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
  void AbstractPlayer::drawCard(Card const *cptr)
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

  AbstractPlayer *AI::selectPlayer(std::vector<AbstractPlayer *> v)
  {
    int idx = std::rand() % v.size();
    return v[idx];
  }

  int AI::selectCard()
  {
    return std::rand() % 8 + 1;
  }

  // Human
  Human::Human(const std::string &s) : AbstractPlayer(s) {}

  Human::~Human() {}

  Card const *Human::playCard()
  {
    if (hand.size() != 2)
      throw std::runtime_error("Invalid size of hand");
    return hand[0];
  }

  AbstractPlayer *Human::selectPlayer(std::vector<AbstractPlayer *> v)
  {
    std::cout << "Select a player index as target\n";
    for (int i = 0; i < v.size(); i++){
      std::cout << i << " : " << v[i]->name << std::endl;
    }
    int idx = -1;
    while (idx < 0 || idx >= v.size()){
      std::cin >> idx;
    }

    return v[idx];
  }

  int Human::selectCard()
  {
    std::cout << "Choose a card number to assassinate: [2-8]\n";
    int n = -1;
    while (n < 2 || n > 8){
      std::cin >> n;
    }
    return n;
  }

} // namespace loveletter