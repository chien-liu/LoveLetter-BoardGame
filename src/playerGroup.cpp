#include "playerGroup.h"
#include "player.h"
#include <string>
#include <vector>

namespace loveletter {
PlayerGroup::PlayerGroup(const std::initializer_list<std::string> &ss, int i)
    : currentId(i) {
  for (auto name : ss) {
    if (name.substr(0, 2) == "AI")
      allPlayers.push_back(new AI(name));
    else
      allPlayers.push_back(new Human(name));
  }
}

PlayerGroup::PlayerGroup(const std::vector<std::string> &ss, int i)
    : currentId(i) {
  for (auto name : ss) {
    if (name.substr(0, 2) == "AI")
      allPlayers.push_back(new AI(name));
    else
      allPlayers.push_back(new Human(name));
  }
}

PlayerGroup::~PlayerGroup() {
  for (auto p : allPlayers) {
    delete p;
  }
}

std::size_t PlayerGroup::size() const { return allPlayers.size(); }

AbstractPlayer *PlayerGroup::operator[](std::size_t idx) {
  return allPlayers[idx];
}

AbstractPlayer const *const PlayerGroup::operator[](std::size_t idx) const {
  return allPlayers[idx];
}

AbstractPlayer *PlayerGroup::current() { return allPlayers[currentId]; }

AbstractPlayer const *PlayerGroup::current() const {
  return allPlayers[currentId];
}

void PlayerGroup::next() {
  int idx = currentId;

  currentId = (currentId + 1) % allPlayers.size();
  while ((*this)[currentId]->isAlive == false && currentId != idx) {
    currentId = (currentId + 1) % allPlayers.size();
  }
}

std::vector<AbstractPlayer *> PlayerGroup::others() {
  std::vector<AbstractPlayer *> others;
  for (auto p : allPlayers) {
    if (p->isAlive && p->name != this->current()->name) {
      others.push_back(p);
    }
  }
  return others;
}

std::vector<AbstractPlayer *> PlayerGroup::all() { return allPlayers; }

int PlayerGroup::numAlivePlayers() const {
  int count = 0;
  for (auto p : allPlayers) {
    count += p->isAlive;
  }
  return count;
}
} // namespace loveletter