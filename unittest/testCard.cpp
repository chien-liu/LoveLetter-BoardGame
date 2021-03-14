#include "gtest/gtest.h"

#define private public
#include "card.h"
#undef private

using namespace loveletter;

TEST(CARD, Constructor) {
  Card card;
  EXPECT_TRUE(card == Card(0));
}

TEST(CARD, Overload) {
  EXPECT_EQ(Card(1), Card(1));
  EXPECT_NE(Card(1), Card(2));
  EXPECT_GT(Card(2), Card(1));
  EXPECT_LT(Card(1), Card(2));
}

TEST(CARDPOOL, Initialization) {
  CardPool pool1(4);
  EXPECT_EQ(pool1.count(), 15);
  CardPool pool2(2);
  EXPECT_EQ(pool2.count(), 13);
}

TEST(CARDPOOL, Next) {
  CardPool pool(4);
  pool.next();
  EXPECT_EQ(pool.count(), 14);
}
