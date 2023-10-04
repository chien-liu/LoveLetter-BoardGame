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
    std::vector<Card const *> hand = {};

    void drawCard(Card const *);

    AbstractPlayer(const std::string &);
    virtual ~AbstractPlayer() = 0;
    virtual Card const *playCard() = 0;
    virtual AbstractPlayer * selectPlayer(std::vector<AbstractPlayer *>) = 0;
    virtual int selectCard() = 0;
  };

  class AI : public AbstractPlayer
  {
  public:
    AI(const std::string &);
    AI(const AI &) = delete;
    ~AI();
    AI &operator=(const AI &) = delete;

    Card const *playCard() override;
    AbstractPlayer * selectPlayer(std::vector<AbstractPlayer *>) override;
    int selectCard() override;
  };

  class Human : public AbstractPlayer
  {
  public:
    Human(const std::string &);
    ~Human();
    Card const *playCard() override;
    AbstractPlayer * selectPlayer(std::vector<AbstractPlayer *>) override;
    int selectCard() override;
  };
} // namespace loveletter
#endif