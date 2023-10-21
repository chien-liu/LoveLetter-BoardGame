#include <iostream>
#include <random>
#include <time.h>

#include "game.h"

int main(int argc, char *argv[]) {
  const int numPlayers = 4; // 4 players
  std::vector<std::string> playerNames;
  playerNames.push_back("Human");
  for (int i = 1; i < numPlayers; i++) {
    playerNames.push_back("AI_" + std::to_string(i));
  }

  srand(time(nullptr));
  int firstPlayerIdx = std::rand() % numPlayers;
  loveletter::Game game(playerNames, firstPlayerIdx);
  printStartMsg(game);

  while (game.notEnd()) {
    printPlayers(game);
    game.drawCard();
    game.playCard();
    game.update();
  }

  printEndMsg(game);

  return 0;
}