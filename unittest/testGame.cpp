#include "gtest/gtest.h"

#define private public
#define protected public
#include "game.h"
#undef private
#undef protected

using namespace loveletter;

TEST(GAME, Initialization) {
  Game game(4);
  EXPECT_FALSE(game.end);
  EXPECT_EQ(game.n_player, 4);
  EXPECT_TRUE(game.pool.count() == 11);
  for (auto p : game.players) {
    EXPECT_NE(p->getHandCard()[0], Card(0));
  }
  EXPECT_GE(game.currentPlayerId, 0);
  EXPECT_LE(game.currentPlayerId, 3);
}

TEST(GAME, DrawCard) {
  Game game(4);
  game.drawCard();
  EXPECT_NE(game.players[game.currentPlayerId]->handCards[1], Card(0));
}

TEST(GAME, Guard) {
  Game game(4);
  game.players[0]->handCards[0] = Card(2);
  game.action.playCard = Card(1);
  game.action.guessCard = Card(2);
  game.action.playerId = 0;
  game.update();
  EXPECT_FALSE(game.players[0]->isAlive);
}

TEST(GAME, Baron) {
  Game game(4);
  game.currentPlayerId = 0;
  game.players[0]->handCards[0] = Card(5);
  game.players[1]->handCards[0] = Card(4);
  game.action.playCard = Card(3);
  game.action.playerId = 1;
  game.update();
  EXPECT_TRUE(game.players[0]->isAlive);
  EXPECT_FALSE(game.players[1]->isAlive);
}

TEST(GAME, King) {
  Game game(4);
  game.currentPlayerId = 0;
  game.players[0]->handCards[0] = Card(5);
  game.players[1]->handCards[0] = Card(4);
  game.action.playCard = Card(6);
  game.action.playerId = 1;
  game.update();
  EXPECT_EQ(game.players[0]->handCards[0], Card(4));
  EXPECT_EQ(game.players[1]->handCards[0], Card(5));
}

TEST(GAME, End){
  Game game(4);
  for (int i = 0; i < 3; i++){
    game.players[i]->isAlive = false;
  }
  game.checkEnd();
  EXPECT_TRUE(game.end);
}