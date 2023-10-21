#include "cardPile.h"
#include "card.h"
#include <assert.h>

#include <algorithm> // std::random_shuffle
#include <iostream>

namespace loveletter {
CardPile::CardPile(int n_player) : top(0) {
  if (n_player < 2 || n_player > 4)
    throw std::runtime_error(
        "CardPile::CardPile(int n_player), more than 4 players.");

  pile.reserve(16);
  for (int i : {1, 1, 1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 7, 8}) {
    pile.push_back(new Card(i));
  }
  std::random_shuffle(pile.begin(), pile.end());

  if (n_player == 2) { // Eliminate two cards from the deck
    for (int i = 0; i < 2; i++) {
      delete pile[i];
    }
    pile.erase(pile.begin(), pile.begin() + 3);
  }
  reserved_card = this->next();
}

CardPile::~CardPile() {
  for (auto card : pile)
    delete card;
}

int CardPile::count() const { return pile.size() - top; }

Card *const CardPile::next() {
  if (top >= pile.size())
    throw std::runtime_error(
        "Card CardPile::next(), attempt to draw an empty CardPile.");
  return pile[top++];
}

Card *const CardPile::GetReservedCard() const { return reserved_card; }
} // namespace loveletter