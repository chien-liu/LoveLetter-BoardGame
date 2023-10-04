#ifndef CARDPILE_H
#define CARDPILE_H

#include "card.h"
namespace loveletter
{
    class CardPile
    {
    public:
        CardPile(int n_player);
        ~CardPile();
        Card *const next();
        Card *const GetReservedCard() const;
        int count() const;

    private:
        std::vector<Card *> pile;
        int top;
        Card *reserved_card;
    };
} // namespace loveletter
#endif