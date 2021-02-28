#include "gtest/gtest.h"
#define private public
#include "card.h"
#include "loveletter.h"
#include "player.h"
#undef private

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

TEST(PLAYER, Initialization) {
  Player p(true);
  EXPECT_TRUE(p.alive);
  EXPECT_EQ(p.hand, Card(0));
  EXPECT_EQ(p.tmp_card, Card(0));
}

TEST(PLAYER, DrawCard) {
  Player p(true);
  p.draw(Card(1));
  EXPECT_EQ(p.hand, Card(1));
  p.draw(Card(2));
  EXPECT_EQ(p.hand, Card(1));
}

TEST(CARDPOOL, Initialization) {
  CardPool pool(4);
  EXPECT_EQ(pool.count(), 15);
}

TEST(CARDPOOL, Next) {
  CardPool pool(4);
  pool.next();
  EXPECT_EQ(pool.count(), 14);
}

TEST(GAME, Initialization) {
  LoveLetter game(4);
  EXPECT_FALSE(game.end());
  EXPECT_TRUE(game.n_player == 4);
  EXPECT_TRUE(game.pool.count() == 11);
  for (auto p : game.players) {
    EXPECT_TRUE(p.tmp_card == Card(0));
    EXPECT_FALSE(p.hand == Card(0));
  }
  EXPECT_GE(game.current_player, 0);
  EXPECT_LE(game.current_player, 3);
}

TEST(GAME, DrawCard) {
  LoveLetter game(4);
  game.drawCard();
  EXPECT_NE(game.players[game.current_player].tmp_card, Card(0));
}

TEST(GAME, Guard) {
  LoveLetter game(4);
  game.players[0].hand = Card(2);
  game.choice.card = Card(1);
  game.choice.guess = Card(2);
  game.choice.player_id = 0;
  game.update();
  EXPECT_FALSE(game.players[0].alive);
}

TEST(GAME, Baron) {
  LoveLetter game(4);
  game.current_player = 0;
  game.players[0].hand = Card(5);
  game.players[1].hand = Card(4);
  game.choice.card = Card(3);
  game.choice.player_id = 1;
  game.update();
  EXPECT_TRUE(game.players[0].alive);
  EXPECT_FALSE(game.players[1].alive);
}

TEST(GAME, King) {
  LoveLetter game(4);
  game.current_player = 0;
  game.players[0].hand = Card(5);
  game.players[1].hand = Card(4);
  game.choice.card = Card(6);
  game.choice.player_id = 1;
  game.update();
  EXPECT_EQ(game.players[0].hand, Card(4));
  EXPECT_EQ(game.players[1].hand, Card(5));
}

TEST(GAME, End){
  LoveLetter game(4);
  for (int i = 0; i < 3; i++){
    game.players[i].alive = false;
  }
  game.checkEnd();
  EXPECT_TRUE(game.end());
}

