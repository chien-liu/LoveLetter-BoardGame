#include "gtest/gtest.h"

#include "card.h"
#include "cardPile.h"

using namespace loveletter;

TEST(CARDPILE, Initialization)
{
  EXPECT_THROW(CardPile(1), std::runtime_error);
  EXPECT_EQ(CardPile(2).count(), 12);
  EXPECT_EQ(CardPile(3).count(), 15);
  EXPECT_EQ(CardPile(4).count(), 15);
  EXPECT_THROW(CardPile(1), std::runtime_error);
}

TEST(CARDPILE, Next)
{
  CardPile pile(4);
  Card *card = pile.next();
  EXPECT_EQ(pile.count(), 14);
}

TEST(CARDPILE, DrawFromEmptyPile)
{
  CardPile pile(4);
  for (int i = 0; i < 15; i++)
    pile.next();
  EXPECT_THROW(pile.next(), std::runtime_error);
}

TEST(CARDPILE, GetReservedCard){
  CardPile pile(4);
  Card* tmp = pile.GetReservedCard(); 
}