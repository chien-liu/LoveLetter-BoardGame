#ifndef PLAYER_GROUP
#define PLAYER_GROUP
#include <vector>
#include "player.h"
namespace loveletter
{
    class PlayerGroup
    {
        std::vector<AbstractPlayer *> allPlayers;
        int numAlivePlayer;

    public:
        int currentId;
        AbstractPlayer *current();
        std::vector<AbstractPlayer *> others();

        PlayerGroup(std::initializer_list<std::string>, int);
        PlayerGroup(const std::vector<std::string> &, int);
        ~PlayerGroup();
        AbstractPlayer *operator[](std::size_t);
        AbstractPlayer const *const operator[](std::size_t) const;
        AbstractPlayer *next();
    };

} // namespace loveletter

#endif