#include "gtest/gtest.h"

#define private public
#include "game.h"
#undef private
#undef protected

#include <string>
#include <vector>
using namespace loveletter;

TEST(GAME, Initialization) {
  std::vector<std::string> ss = {"AI_1", "AI_2", "AI_3", "AI_4"};
  Game game(ss, 0);
  EXPECT_TRUE(game.notEnd());
  EXPECT_EQ(game.players.size(), 4);
  EXPECT_TRUE(game.pile.count() == 11);
  for (auto p : game.players.all()) {
    EXPECT_NE(p->hand[0], nullptr);
  }
  EXPECT_EQ(game.players.currentId, 0);
}

TEST(GAME, DrawCard) {
  std::vector<std::string> ss = {"AI_1", "AI_2", "AI_3", "AI_4"};
  Game game(ss, 0);
  game.drawCard();
  EXPECT_NE(game.players.current()->hand[1], nullptr);
}

TEST(GAME, Guard) {
  std::vector<std::string> ss = {"AI_1", "AI_2", "AI_3", "AI_4"};
  Game game(ss, 0);
  Card card1{1};
  Card card2{2};
  game.players[1]->hand[0] = &card2;
  game.activateCardptr = &card1;
  game.assassinatedCardNumber = 2;
  game.targetPlayer = game.players[1];
  game.update();
  EXPECT_FALSE(game.players[1]->isAlive);
}

// TEST(GAME, GuardSelf)
// {
//   Game game(4);
//   game.currentPlayerId = 0;
//   game.players[0]->handCards[0] = Card(2);
//   game.action.playCard = Card(1);
//   game.action.guessCard = Card(2);
//   game.action.playerId = 0;
//   game.update();
//   EXPECT_TRUE(game.players[0]->isAlive);
// }

// TEST(GAME, Baron)
// {
//   Game game(4);
//   game.currentPlayerId = 0;
//   game.players[0]->handCards[0] = Card(5);
//   game.players[1]->handCards[0] = Card(4);
//   game.action.playCard = Card(3);
//   game.action.playerId = 1;
//   game.update();
//   EXPECT_TRUE(game.players[0]->isAlive);
//   EXPECT_FALSE(game.players[1]->isAlive);
// }

// TEST(GAME, King)
// {
//   Game game(4);
//   game.currentPlayerId = 0;
//   game.players[0]->handCards[0] = Card(5);
//   game.players[1]->handCards[0] = Card(4);
//   game.action.playCard = Card(6);
//   game.action.playerId = 1;
//   game.update();
//   EXPECT_EQ(game.players[0]->handCards[0], Card(4));
//   EXPECT_EQ(game.players[1]->handCards[0], Card(5));
// }

// TEST(GAME, KingSelf)
// {
//   Game game(4);
//   game.currentPlayerId = 0;
//   game.players[0]->handCards[0] = Card(5);
//   game.action.playCard = Card(6);
//   game.action.playerId = 0;
//   game.update();
//   EXPECT_EQ(game.players[0]->handCards[0], Card(5));
// }

// TEST(GAME, End)
// {
//   Game game(4);
//   for (int i = 0; i < 3; i++)
//   {
//     game.players[i]->isAlive = false;
//   }
//   game.checkEnd();
//   EXPECT_TRUE(game.end);
// }