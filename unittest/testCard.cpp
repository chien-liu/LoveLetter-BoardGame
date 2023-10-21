#include "card.h"
#include "gtest/gtest.h"

using namespace loveletter;

TEST(CARD, ConstructorSuccess) {
  Card card{1};
  Card card2 = card;
  Card card3 = Card(8);
}

TEST(CARD, ConstructorFail) {
  EXPECT_THROW(Card(0), std::invalid_argument);
  EXPECT_THROW(Card(9), std::invalid_argument);
}

TEST(CARD, Comparison) {
  Card card1{1};
  Card card2{2};
  EXPECT_EQ(card1, card1);
  EXPECT_NE(card1, card2);

  EXPECT_GT(card2, card1);
  EXPECT_LT(card1, card2);

  EXPECT_GE(card2, card1);
  EXPECT_GE(card1, card1);
  EXPECT_LE(card1, card2);
  EXPECT_LE(card1, card1);
}
