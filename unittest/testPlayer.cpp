#include "gtest/gtest.h"

#include "card.h"
#include "player.h"

using namespace loveletter;

TEST(PLAYER, Initialization) {
  AI ai{"MyAI"};
  EXPECT_TRUE(ai.isAlive);
  EXPECT_FALSE(ai.isProtected);
  EXPECT_TRUE(ai.hand.empty());

  Human h{"Chien"};
  EXPECT_TRUE(h.isAlive);
  EXPECT_FALSE(h.isProtected);
  EXPECT_TRUE(h.hand.empty());
}

TEST(PLAYER, DrawCard) {
  Card c1{1};
  Card c2{2};
  AI ai{"AI"};
  ai.drawCard(&c1);
  EXPECT_EQ(*ai.hand[0], Card(1));
  ai.drawCard(&c2);
  EXPECT_EQ(*ai.hand[1], Card(2));

  Card c3{3};
  Card c4{4};
  Human h{"Chien"};
  h.drawCard(&c3);
  EXPECT_EQ(*h.hand[0], Card(3));
  h.drawCard(&c4);
  EXPECT_EQ(*h.hand[1], Card(4));
}

TEST(PLAYER, PlayCardSucceed) {
  Card c1{1};
  Card c2{1};
  AI ai{"ai"};
  ai.drawCard(&c1);
  ai.drawCard(&c2);
  ai.playCard();
  EXPECT_EQ(*ai.hand[0], Card(1));
}

TEST(PLAYER, PlayCardFail) {
  Card c1{1};
  Card c2{2};
  Card c3{3};
  AI ai{"ai"};
  EXPECT_THROW(ai.playCard(), std::runtime_error); // not enough cards in hand
  ai.drawCard(&c1);
  EXPECT_THROW(ai.playCard(), std::runtime_error); // not enough cards in hand
  ai.drawCard(&c2);
  ai.drawCard(&c3);
  EXPECT_THROW(ai.playCard(), std::runtime_error); // too many cards in hand

  Card c4{4};
  Card c5{5};
  Card c6{6};
  Human h{"Chien"};
  EXPECT_THROW(h.playCard(), std::runtime_error); // not enough cards in hand
  h.drawCard(&c4);
  EXPECT_THROW(h.playCard(), std::runtime_error); // not enough cards in hand
  h.drawCard(&c5);
  h.drawCard(&c6);
  EXPECT_THROW(h.playCard(), std::runtime_error); // too many cards in hand
}
