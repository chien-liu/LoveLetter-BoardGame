#include "playerGroup.h"
#include "gtest/gtest.h"
#include <string>
#include <vector>

using namespace loveletter;

TEST(PlayerGroup, Initialization) {
  std::vector<std::string> ss = {"player_A", "player_B"};
  int start_id = 0;
  PlayerGroup *players = new PlayerGroup(ss, start_id);

  EXPECT_EQ(players->currentId, 0);
  EXPECT_EQ(players->current()->name, "player_A");

  start_id = 1;
  PlayerGroup *players2 = new PlayerGroup(ss, start_id);
  EXPECT_EQ(players2->currentId, 1);
  EXPECT_EQ(players2->current()->name, "player_B");

  delete players;
  delete players2;
}

TEST(PlayerGroup, OverloadArraySubscriptOperator) {
  std::vector<std::string> ss = {"player_A", "player_B"};
  int start_id = 0;
  PlayerGroup players{ss, start_id};
  EXPECT_EQ(players[0]->name, "player_A");
  EXPECT_EQ(players[1]->name, "player_B");
}

TEST(PlayerGroup, CreateAIandHuman) {
  std::vector<std::string> ss = {"AI_player_A", "player_B"};
  int start_id = 0;
  PlayerGroup players{ss, start_id};
  EXPECT_EQ(typeid(*players[0]), typeid(AI));
  EXPECT_EQ(typeid(*players[1]), typeid(Human));
}

TEST(PlayerGroup, Next) {
  std::vector<std::string> ss = {"player_A", "player_B"};
  int start_id = 0;
  PlayerGroup *players = new PlayerGroup(ss, start_id);

  players->next();
  EXPECT_EQ(players->currentId, 1);
  EXPECT_EQ(players->current()->name, "player_B");

  players->next();
  EXPECT_EQ(players->currentId, 0);
  EXPECT_EQ(players->current()->name, "player_A");
  delete players;
}

TEST(PlayerGroup, NextExcludeDeath) {
  std::vector<std::string> ss = {"player_A", "player_B", "player_C"};
  int start_id = 0;
  PlayerGroup players = PlayerGroup(ss, start_id);
  players[1]->isAlive = false;
  players.next();

  EXPECT_EQ(players.currentId, 2);
  EXPECT_EQ(players.current()->name, "player_C");
}

TEST(PlayerGroup, Others) {
  std::vector<std::string> ss = {"player_A", "player_B"};
  int start_id = 0;
  PlayerGroup *players = new PlayerGroup(ss, start_id);
  EXPECT_EQ(players->others().size(), 1);
  EXPECT_EQ(players->others()[0]->name, "player_B");

  players->next();
  EXPECT_EQ(players->others().size(), 1);
  EXPECT_EQ(players->others()[0]->name, "player_A");
  delete players;
}

TEST(PlayerGroup, OthersExcludeDeath) {
  std::vector<std::string> ss = {"player_A", "player_B", "player_C"};
  int start_id = 0;
  PlayerGroup players{ss, start_id};
  players[1]->isAlive = false;

  EXPECT_EQ(players.others().size(), 1);
  EXPECT_EQ(players.others()[0]->name, "player_C");
}

TEST(PlayerGroup, numAlivePlayers) {
  std::vector<std::string> ss = {"player_A", "player_B", "player_C"};
  int start_id = 0;
  PlayerGroup players{ss, start_id};
  EXPECT_EQ(players.numAlivePlayers(), 3);

  players[2]->isAlive = false;
  EXPECT_EQ(players.numAlivePlayers(), 2);

  players[1]->isAlive = false;
  EXPECT_EQ(players.numAlivePlayers(), 1);
}