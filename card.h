#ifndef CARD_H
#define CARD_H
#include <map>
#include <vector>

class Card {
 public:
  Card() : num(0){};
  Card(int n) : num(n){};
  int getNum() const { return this->num; }
  std::string getName() const { return dict.at(num); }

 private:
  int num;
  static const std::map<int, std::string> dict;
};

bool operator==(const Card& lhs, const Card& rhs);
bool operator!=(const Card& lhs, const Card& rhs);
bool operator>(const Card& lhs, const Card& rhs);
bool operator<(const Card& lhs, const Card& rhs);

class CardPool {
 public:
  CardPool(int n_player);
  Card next();
  Card specialDraw();
  int count() { return order.size(); }

 private:
  std::vector<Card> order;
  Card reserved_card;
};

#endif