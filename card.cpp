#include "card.h"

#include <assert.h>

#include <algorithm>  // std::random_shuffle
#include <iostream>
using namespace std;

const map<int, string> Card::dict = {
    {1, "Guard"},  {2, "Priest"}, {3, "Baron"},    {4, "Handmaid"},
    {5, "Prince"}, {6, "King"},   {7, "Countess"}, {8, "Princess"}};

bool operator==(const Card& lhs, const Card& rhs) {
  return lhs.getNum() == rhs.getNum();
}
bool operator!=(const Card& lhs, const Card& rhs) {
  return lhs.getNum() != rhs.getNum();
}
bool operator>(const Card& lhs, const Card& rhs) {
  return lhs.getNum() > rhs.getNum();
}
bool operator<(const Card& lhs, const Card& rhs) {
  return lhs.getNum() < rhs.getNum();
}

CardPool::CardPool(int n_player) {
  for (auto i : {1, 1, 1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 7, 8}) {
    this->order.push_back(Card(i));
  }
  random_shuffle(this->order.begin(), this->order.end());

  reserved_card = this->next();
  if (n_player == 2) {
    order.erase(order.begin(), order.begin() + 2);
  }
}

Card CardPool::next() {
  assert(this->order.size() > 0 && "No more cards");
  Card card = this->order.back();
  this->order.pop_back();
  return card;
}

Card CardPool::specialDraw() {
  assert(this->order.size() == 0 && "Invalid Action: Special Draw");
  Card card = reserved_card;
  reserved_card = Card(0);
  return card;
}