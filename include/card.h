#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <map>
#include <vector>

namespace loveletter {
class Card {
 public:
  Card() : num(0), name(nullptr){};
  Card(int n) : num(n), name(dict.at(num)){};

  int getNum() const noexcept { return num; }
  const char* getName() const noexcept { return name; }

  bool operator==(const Card& other) const;
  bool operator!=(const Card& other) const;
  bool operator>(const Card& other) const;
  bool operator<(const Card& other) const;

  friend std::ostream& operator<<(std::ostream& stream, const Card& card);

 private:
  int num;
  const char* name;
  static const std::map<int, const char*> dict;
};

class CardPool {
 public:
  CardPool(int n_player);
  Card next();
  Card GetReservedCard();
  int count() const { return pile.size(); }

 private:
  std::vector<Card> pile;
  Card reserved_card;
};
}  // namespace loveletter
#endif