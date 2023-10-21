#ifndef PLAYER_GROUP
#define PLAYER_GROUP
#include "player.h"
#include <vector>
namespace loveletter {
class PlayerGroup {
  std::vector<AbstractPlayer *> allPlayers;

public:
  int currentId;
  std::size_t size() const;
  int numAlivePlayers() const;
  AbstractPlayer *current();
  AbstractPlayer const *current() const;
  std::vector<AbstractPlayer *> others();
  std::vector<AbstractPlayer *> all();

  PlayerGroup(const std::initializer_list<std::string> &, int);
  PlayerGroup(const std::vector<std::string> &, int);
  ~PlayerGroup();
  AbstractPlayer *operator[](std::size_t);
  AbstractPlayer const *const operator[](std::size_t) const;
  void next();
};

} // namespace loveletter

#endif