#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>
#include "card.h"
namespace loveletter
{
  class AbstractPlayer
  {
  public:
    const std::string name;
    bool isAlive = true;
    bool isProtected = false;
    std::vector<Card> hand = {};

    void drawCard(Card *);

    AbstractPlayer(std::string s);
    virtual ~AbstractPlayer() = 0;
    virtual Card playCard() = 0;
    // virtual const std::string &choosePlayer(std::vector<std::string &>) = 0;
    // virtual int chooseCardId() = 0;
  };

  class AI : public AbstractPlayer
  {
  public:
    AI(std::string);
    AI(const AI &) = delete;
    ~AI();
    AI &operator=(const AI &) = delete;

    Card playCard() override;
    // const std::string &choosePlayer(std::vector<std::string &>) override;
    // int chooseCardId() override;
  };

  class Human : public AbstractPlayer
  {
  public:
    Human(std::string s);
    ~Human();
    Card playCard() override;
    // const std::string &choosePlayer(std::vector<std::string &>) override;
    // int chooseCardId() override;

  // private:
  //   bool leftOrRight();
  };
} // namespace loveletter
#endif