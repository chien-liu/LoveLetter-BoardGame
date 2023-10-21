#include "card.h"

#include <assert.h>

#include <algorithm> // std::random_shuffle
#include <iostream>

namespace loveletter {
Card::Card(int n) : num(n), name(initializeName(n)){};
Card::Card(const Card &card) : num(card.getNum()), name(card.getName()){};

const std::string &Card::initializeName(int n) {
  if (n < 1 || n > 8)
    throw std::invalid_argument(
        "Card::Card(int n), n needs to be in the range of [1, 8].\n");
  return dict.at(n);
}

int Card::getNum() const noexcept { return num; }
const std::string &Card::getName() const noexcept { return name; }

bool Card::operator==(const Card &other) const { return num == other.getNum(); }
bool Card::operator!=(const Card &other) const { return !operator==(other); }
bool Card::operator>(const Card &other) const { return num > other.getNum(); }
bool Card::operator<(const Card &other) const { return num < other.getNum(); }
bool Card::operator>=(const Card &other) const { return num >= other.getNum(); }
bool Card::operator<=(const Card &other) const { return num <= other.getNum(); }

std::ostream &operator<<(std::ostream &stream, const Card &card) {
  stream << card.name << "(" << card.num << ")";
  return stream;
}

const std::map<int, const std::string> Card::dict = {
    {0, ""},      {1, "Guard"},    {2, "Priest"},
    {3, "Baron"}, {4, "Handmaid"}, {5, "Prince"},
    {6, "King"},  {7, "Countess"}, {8, "Princess"}};
} // namespace loveletter