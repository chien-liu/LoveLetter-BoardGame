#include "game.h"

#include <assert.h>
#include <time.h>

#include <algorithm>  // std::random_shuffle
#include <random>
#include <string>
#include <vector>

namespace loveletter {
Game::Game(const int n)
    : n_player(n),
      round(1),
      end(false),
      pool(n_player),
      currentPlayerId(rand() % n_player) {
  constructPlayers();
}

Game::~Game() { destructPlayers(); }

void Game::printStartMsg() const {
  std::cout << "[Loveletter]" << std::endl
            << n_player << "players" << std::endl;
}
void Game::printEndMsg() const {
  assert(winnerIds.size() > 0 && "No one wins.");
  std::cout << "Game end" << std::endl << "Player " << winnerIds[0];
  if (winnerIds.size() > 1) {
    for (int i = 1; i < (int)winnerIds.size(); i++) {
      std::cout << ", " << winnerIds[i];
    }
    std::cout << " win!" << std::endl;
  } else {
    std::cout << " wins!" << std::endl;
  }
}
void Game::drawCard() { players[currentPlayerId]->draw(pool.next()); }

void Game::printPlayer() const {
  std::string c[4] = {};
  for (int i = 0; i < 4; i++) {
    if (players[i]->isAlive && players[i]->isSave) {
      c[i] = "\u0394";  // Δ
    } else if (players[i]->isAlive) {
      c[i] = "O";
    } else {
      c[i] = "X";
    }
  }
  std::cout << "---------------------" << std::endl
            << "[Game info] Round:" << round << ". Turn to Player "
            << currentPlayerId << std::endl;
  if (currentPlayerId == 0) {  // Human Player
    std::cout << "Cards remains in card pool: " << pool.count() << std::endl;
  }
  std::cout << "\tp2:" << c[2] << std::endl
            << "p1:" << c[1] << "\t\t"
            << "p3:" << c[3] << std::endl
            << "\tp0:" << c[0] << std::endl;
}

void loveletter::Game::executeAction() {
  std::vector<int> avail_playerId;

  // available people
  for (int i = 0; i < n_player; i++) {
    if ((players[i]->isAlive) && (i != currentPlayerId) &&
        !(players[i]->isSave)) {
      avail_playerId.push_back(i);
    }
  }
  if (avail_playerId.size() == 0) {
    avail_playerId.push_back(currentPlayerId);
  }

  action = players[currentPlayerId]->executeAction(avail_playerId);
}

static void switchHandCard(Player* lhs, Player* rhs) {
  Card tmp = lhs->getHandCard()[0];
  lhs->switchCard(rhs->getHandCard()[0]);
  rhs->switchCard(tmp);
}

void loveletter::Game::update() {
  std::cout << "[Game Info] Player " << currentPlayerId << " use "
            << action.playCard << std::endl;
  players[currentPlayerId]->isSave = false;
  switch (action.playCard.getNum()) {
    case 1:
      std::cout << "[Game Info] Target Player " << action.playerId << std::endl
                << "[Game Info] Guess card " << action.guessCard << std::endl;
      if (players[action.playerId]->getHandCard()[0] == action.guessCard) {
        players[action.playerId]->isAlive = false;
        std::cout << "[Game Info] Player " << action.playerId << " is dead."
                  << std::endl;
      }
      break;
    case 2:
      std::cout << "[Game Info] Target Player " << action.playerId << std::endl
                << "[Game Info] Player" << action.playerId << "'s card is "
                << players[action.playerId]->getHandCard()[0] << std::endl;
      break;
    case 3:
      std::cout << "[Game Info] Target Player " << action.playerId << std::endl;
      if (players[currentPlayerId]->getHandCard()[0] >
          players[action.playerId]->getHandCard()[0]) {
        players[action.playerId]->isAlive = false;
        std::cout << "[Game Info] Player " << action.playerId
                  << " is dead, holding the card "
                  << players[action.playerId]->getHandCard()[0] << std::endl;
      } else if (players[currentPlayerId]->getHandCard()[0] <
                 players[action.playerId]->getHandCard()[0]) {
        players[currentPlayerId]->isAlive = false;
        std::cout << "[Game Info] Player " << currentPlayerId
                  << " is dead, holding the card "
                  << players[currentPlayerId]->getHandCard()[0] << std::endl;
      }
      break;
    case 4:
      players[currentPlayerId]->isSave = true;
      break;
    case 5:
      std::cout << "[Game Info] Target Player " << action.playerId << std::endl;
      players[action.playerId]->discard();
      if (pool.count() > 0) {
        players[action.playerId]->draw(pool.next());
      } else {
        players[action.playerId]->draw(pool.GetReservedCard());
      }
      break;
    case 6: {
      std::cout << "[Game Info] Target Player " << action.playerId << std::endl;
      switchHandCard(players[action.playerId], players[currentPlayerId]);
      break;
    }
    case 7:
      break;
    case 8:
      players[currentPlayerId]->isAlive = false;
      std::cout << "[Game info] Player " << currentPlayerId
                << " discard the princess." << std::endl
                << "[Game info] Player " << currentPlayerId << " is dead"
                << std::endl;
      break;

    default:
      break;
  }

  // update index of next player
  do {
    currentPlayerId++;
    if (currentPlayerId == n_player) {
      currentPlayerId = 0;
    }
  } while (!players[currentPlayerId]->isAlive);

  // update round counter
  round++;
}

void loveletter::Game::checkEnd() {
  if (!pool.count()) {
    end = true;
    std::cout << "[Game Status] Game end: Card pool is out of cards."
              << std::endl;
    return;
  }
  int count = 0;
  for (int i = 0; i < (int)players.size(); i++) {
    count += players[i]->isAlive;
  }
  assert(count && "Error: All player dead.");
  if (count == 1) {
    end = true;
    std::cout << "[Game Status] Game end: Last player survived." << std::endl;
    return;
  }
}

void loveletter::Game::updateWinner() {
  Card card;  // 0
  std::cout << "------------------" << std::endl;
  std::cout << "Player\tCard" << std::endl;
  // Check largest card
  // Check winner
  for (int i = 0; i < (int)players.size(); i++) {
    assert(players[i]->getHandCard().size() == 1);
    if (players[i]->isAlive) {
      std::cout << i << "\t" << players[i]->getHandCard()[0] << std::endl;
      if (players[i]->getHandCard()[0] > card) {
        winnerIds = {};
        winnerIds.push_back(i);
        card = players[i]->getHandCard()[0];
      } else if (players[i]->getHandCard()[0] == card) {
        winnerIds.push_back(i);
      }
    }
  }
}

void Game::constructPlayers() {
  // Set up Human player
  Human* ph = new Human(0);
  ph->draw(pool.next());
  players.push_back(ph);
  // Set up AI player
  for (int i = 1; i < n_player; i++) {
    AI* pa = new AI(i);
    pa->draw(pool.next());
    players.push_back(pa);
  }
}

void Game::destructPlayers() {
  for (int i = 0; i < n_player; i++) {
    delete players[i];
  }
}
}  // namespace loveletter