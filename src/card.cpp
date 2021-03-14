#include "card.h"

#include <assert.h>

#include <algorithm>  // std::random_shuffle
#include <iostream>

namespace loveletter{

bool Card::operator==(const Card& other) const { return num == other.getNum(); }
bool Card::operator!=(const Card& other) const { return !operator==(other); }
bool Card::operator>(const Card& other) const { return num > other.getNum(); }
bool Card::operator<(const Card& other) const { return num < other.getNum(); }


std::ostream& operator<<(std::ostream& stream, const Card& card) {
  stream << card.name << "(" << card.num << ")";
  return stream;
}

const std::map<int, const char*> Card::dict = {
    {0, ""},      {1, "Guard"},    {2, "Priest"},
    {3, "Baron"}, {4, "Handmaid"}, {5, "Prince"},
    {6, "King"},  {7, "Countess"}, {8, "Princess"}};

CardPool::CardPool(int n_player) {
  pile.reserve(16);
  for (int i : {1, 1, 1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 7, 8}) {
    pile.push_back(std::move(Card(i)));
  }
  std::random_shuffle(pile.begin(), pile.end());

  reserved_card = next();
  if (n_player == 2) {
    pile.erase(pile.begin(), pile.begin() + 2);
  }
}

Card CardPool::next() {
  assert(pile.size() > 0 && "No more cards");
  Card card = pile.back();
  pile.pop_back();
  return card;
}

Card CardPool::GetReservedCard() {
  assert(pile.size() == 0 && "Invalid Action: Special Draw");
  Card card = reserved_card;
  reserved_card = Card(0);
  return card;
}
}