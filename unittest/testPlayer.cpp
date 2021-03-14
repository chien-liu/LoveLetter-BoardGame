#include "gtest/gtest.h"

#define private public
#define protected public
#include "player.h"
#undef private
#undef protected

using namespace loveletter;

TEST(PLAYER, Initialization) {
  AI p(0);
  EXPECT_EQ(p.id, 0);
  EXPECT_TRUE(p.isAlive);
  EXPECT_TRUE(p.getHandCard().empty());
  EXPECT_FALSE(p.isSave);
}

TEST(PLAYER, DrawCard) {
  AI p(0);
  p.draw(Card(1));
  EXPECT_EQ(p.getHandCard()[0], Card(1));
  p.draw(Card(2));
  EXPECT_EQ(p.getHandCard()[1], Card(2));
}

TEST(PLAYER, Discard) {
  AI p(0);
  p.draw(Card(1));
  p.discard();
  EXPECT_TRUE(p.getHandCard().empty());
}

TEST(PLAYER, DiscardPrincess) {
  AI p(0);
  p.draw(Card(8));
  p.discard();
  EXPECT_FALSE(p.isAlive);
}

TEST(PLAYER, ExecuteAction1) {
  AI p(0);
  p.draw(Card(1));
  p.draw(Card(1));
  PlayerAction action = p.executeAction({1, 2, 3});
  EXPECT_EQ(action.playCard, Card(1));
  EXPECT_NE(action.guessCard, Card(1));
  EXPECT_NE(action.guessCard, Card(0));
  EXPECT_NE(action.playerId, 0);
  EXPECT_NE(action.playerId, -1);
}