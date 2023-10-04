#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <map>
#include <vector>
#include <string>

namespace loveletter
{
  class Card
  {
  public:
    Card(int);
    Card(const Card &);

    int getNum() const noexcept;
    const std::string &getName() const noexcept;

    bool operator==(const Card &) const;
    bool operator!=(const Card &) const;
    bool operator>(const Card &) const;
    bool operator<(const Card &) const;
    bool operator>=(const Card &) const;
    bool operator<=(const Card &) const;

    friend std::ostream &operator<<(std::ostream &, const Card &);

  private:
    int num;
    std::string name;
    static const std::map<int, const std::string> dict;
    const std::string &initializeName(int);
  };
} // namespace loveletter
#endif