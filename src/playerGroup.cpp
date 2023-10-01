#include <vector>
#include <string>
#include "player.h"
#include "playerGroup.h"

namespace loveletter
{
    PlayerGroup::PlayerGroup(std::initializer_list<std::string> ss, int i)
        : currentId(i),
          numAlivePlayer(ss.size())
    {
        for (auto name : ss)
        {
            if (name.substr(0, 2) == "AI")
                allPlayers.push_back(new AI(name));
            else
                allPlayers.push_back(new Human(name));
        }
    }

    PlayerGroup::PlayerGroup(const std::vector<std::string> &ss, int i)
        : currentId(i),
          numAlivePlayer(ss.size())
    {
        for (auto name : ss)
        {
            if (name.substr(0, 2) == "AI")
                allPlayers.push_back(new AI(name));
            else
                allPlayers.push_back(new Human(name));
        }
    }

    PlayerGroup::~PlayerGroup()
    {
        for (auto p : allPlayers)
        {
            delete p;
        }
    }

    AbstractPlayer *PlayerGroup::operator[](std::size_t idx)
    {
        return allPlayers[idx];
    }

    AbstractPlayer const *const PlayerGroup::operator[](std::size_t idx) const
    {
        return allPlayers[idx];
    }

    AbstractPlayer *PlayerGroup::current()
    {
        return allPlayers[currentId];
    }

    AbstractPlayer *PlayerGroup::next()
    {
        int idx = currentId;

        currentId = (currentId + 1) % numAlivePlayer;
        while ((*this)[currentId]->isAlive == false && currentId != idx)
        {
            currentId = (currentId + 1) % numAlivePlayer;
        }
        return (*this)[currentId];
    }

    std::vector<AbstractPlayer *> PlayerGroup::others()
    {
        std::vector<AbstractPlayer *> others;
        for (auto p : allPlayers)
        {
            if (p->isAlive && p->name!=this->current()->name)
            {
                others.push_back(p);
            }
        }
        return others;
    }
}