#include "game.h"
#include <random>
#include <string>
#include <vector>

namespace loveletter {

Game::Game(const std::vector<std::string> &ss, int firstPlayerIdx)
    : pile(ss.size()), players(ss, firstPlayerIdx) {
  for (int i = 0; i < ss.size(); i++) {
    this->drawCard();
    players.next();
  }
}

Game::~Game() {}

void Game::drawCard() { players.current()->drawCard(pile.next()); }

void Game::playCard() {
  targetPlayer = nullptr;      // initialized
  assassinatedCardNumber = -1; // initialized

  activateCardptr = players.current()->playCard();
  switch (activateCardptr->getNum()) {
  case 1:
    targetPlayer = players.current()->selectPlayer(players.others());
    assassinatedCardNumber = players.current()->selectCard();
    break;
  case 2:
  case 3:
  case 5:
    targetPlayer = players.current()->selectPlayer(players.others());
    break;
  case 6:
    targetPlayer = players.current()->selectPlayer(players.all());
  }
  std::cout << "[Game Info] Player " << players.current()->name << " uses "
            << *activateCardptr << std::endl;
}

void Game::update() {
  players.current()->isProtected = false;
  switch (activateCardptr->getNum()) {
  case 1:
    std::cout << "[Game Info] Target Player " << targetPlayer->name << std::endl
              << "[Game Info] Guess card " << assassinatedCardNumber
              << std::endl;
    if (targetPlayer->hand[0]->getNum() == assassinatedCardNumber) {
      targetPlayer->isAlive = false;
      std::cout << "[Game Info] Player " << targetPlayer->name << " is dead."
                << std::endl;
    }
    break;
  case 2:
    if (typeid(*players.current()) == typeid(AI)) {
      break;
    }
    std::cout << "[Game Info] Target Player " << targetPlayer->name << std::endl
              << "[Game Info] Player" << targetPlayer->name << "'s card is "
              << targetPlayer->hand[0] << std::endl;
    break;
  case 3:
    std::cout << "[Game Info] Target Player " << targetPlayer->name
              << std::endl;
    if (players.current()->hand[0] > targetPlayer->hand[0]) {
      targetPlayer->isAlive = false;
      std::cout << "[Game Info] Player " << targetPlayer->name
                << " is dead, holding the card " << *targetPlayer->hand[0]
                << std::endl;
    } else if (players.current()->hand[0] < targetPlayer->hand[0]) {
      players.current()->isAlive = false;
      std::cout << "[Game Info] Player " << players.current()->name
                << " is dead, holding the card " << *players.current()->hand[0]
                << std::endl;
    }
    break;
  case 4:
    players.current()->isProtected = true;
    break;
  case 5:
    std::cout << "[Game Info] Target Player " << targetPlayer->name
              << std::endl;
    targetPlayer->hand.pop_back();
    if (pile.count() > 0) {
      targetPlayer->drawCard(pile.next());
    } else {
      targetPlayer->drawCard(pile.GetReservedCard());
    }
    break;
  case 6: {
    std::cout << "[Game Info] Target Player " << targetPlayer->name
              << std::endl;
    std::swap(players.current()->hand[0], targetPlayer->hand[0]);
    break;
  }
  case 7:
    break;
  case 8:
    players.current()->isAlive = false;
    std::cout << "[Game info] Player " << players.current()->name
              << " discard the princess." << std::endl
              << "[Game info] Player " << players.current()->name << " is dead"
              << std::endl;
    break;

  default:
    break;
  }

  // update index of next player
  players.next();

  // update round counter
  currentRound++;
}

bool Game::notEnd() const {
  if (pile.count() == 0) {
    std::cout << "[Game Status] Game end: Card pile is out of cards.\n";
    return false;
  }

  if (players.numAlivePlayers() == 1) {
    std::cout << "[Game Status] Game end: Last player survived.\n";
    return false;
  }

  return true;
}

std::vector<AbstractPlayer const *> Game::checkWinner() const {
  Card const *maxCardptr = nullptr;
  std::vector<AbstractPlayer const *> winners;

  std::cout << "------------------" << std::endl;
  std::cout << "Player\tCard" << std::endl;
  // Check largest card
  // Check winner
  for (int i = 0; i < players.size(); i++) {
    if (!players[i]->isAlive) {
      std::cout << players[i]->name << '\t' << "Dead\n";
      continue;
    }

    std::cout << i << "\t" << *players[i]->hand[0] << std::endl;
    if (!maxCardptr || *players[i]->hand[0] > *maxCardptr) {
      winners = {};
      winners.push_back(players[i]);
      maxCardptr = players[i]->hand[0];
    } else if (*players[i]->hand[0] == *maxCardptr) {
      winners.push_back(players[i]);
    }
  }
  if (winners.size() == 0)
    throw std::runtime_error("No winners.");
  return winners;
}

void printStartMsg(const Game &game) {
  std::cout << "[Loveletter]" << std::endl
            << "Number of players: " << game.players.size() << std::endl;
}

void printEndMsg(const Game &game) {
  std::vector<AbstractPlayer const *> winners = game.checkWinner();
  std::cout << "Game end" << std::endl << "Player " << winners[0]->name;
  if (winners.size() > 1) {
    for (int i = 1; i < (int)winners.size(); i++) {
      std::cout << ", " << winners[i];
    }
  }
  std::cout << " win!" << std::endl;
}

void printPlayers(const Game &game) {
  std::string c[4] = {};
  for (int i = 0; i < 4; i++) {
    if (game.players[i]->isAlive && game.players[i]->isProtected) {
      c[i] = "\u0394"; // Δ
    } else if (game.players[i]->isAlive) {
      c[i] = "O";
    } else {
      c[i] = "X";
    }
  }
  std::cout << "---------------------\n"
            << "[Game info] Round:" << game.currentRound << ". Turn to Player "
            << game.players.current()->name << std::endl;

  if (typeid(*game.players.current()) == typeid(Human)) { // Human Player
    std::cout << "# of cards remaining in the pile: " << game.pile.count()
              << std::endl;
  }
  std::cout << '\t' << game.players[2]->name << ':' << c[2] << std::endl
            << game.players[1]->name << ':' << c[1] << "\t\t"
            << game.players[3]->name << ':' << c[3] << std::endl
            << '\t' << game.players[0]->name << ':' << c[0] << std::endl;
}
} // namespace loveletter