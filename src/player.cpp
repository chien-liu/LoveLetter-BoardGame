#include "player.h"

#include <assert.h>
#include <stdio.h>

#include <algorithm>
#include <iostream>
#include <random>

#include "card.h"

#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_RIGHT 67
#define KEY_LEFT 68

namespace loveletter {

void Player::draw(Card card) {
  assert(handCards.size() < 2 && "Draw a card when already having two cards.");
  handCards.push_back(card);
}

void Player::discard() {
  assert(handCards.size() < 2 && "Cannot discard when holding two cards.");
  if (handCards[0] == Card(8)) {
    isAlive = false;
    std::cout << "[Game info] Player " << id << " discard the princess."
              << std::endl
              << "[Game info] Player " << id << " is dead" << std::endl;
  }
  handCards.pop_back();
}

std::vector<int> Player::getAvailCardId() {
  // princess
  if (handCards[0] == Card(8))
    return {1};
  else if (handCards[1] == Card(8))
    return {0};

  // countess
  if (handCards[0] == Card(7) &&
      (handCards[1] == Card(5) || handCards[1] == Card(6)))
    return {0};
  else if (handCards[1] == Card(7) &&
           (handCards[0] == Card(5) || handCards[0] == Card(6)))
    return {1};

  // else
  return {0, 1};
}

PlayerAction AI::executeAction(std::vector<int> avail_playerId) {
  assert(handCards.size() == 2 &&
         "Execute an action when holding cards less than 2.");

  std::vector<int> avail_card = getAvailCardId();
  PlayerAction action;

  // PlayerAction.playCard
  random_shuffle(avail_card.begin(), avail_card.end());
  action.playCard = handCards.at(avail_card.back());
  handCards.erase(handCards.begin() + avail_card.back());

  // PlayerAction.playerId
  random_shuffle(avail_playerId.begin(), avail_playerId.end());
  if (!avail_playerId.empty()) {
    action.playerId = avail_playerId.back();
  }

  // PlayerAction.guessCard
  action.guessCard = Card(rand() % 7 + 2);

  return action;
}

static int HumanChooseCardInterface() {
  int id;
  char c;
  system("stty raw");
  while (1) {
    if (getchar() == 27)
      if (getchar() == 91) {
        c = getchar();
        if (c == KEY_LEFT) {
          id = 0;
          break;
        } else if (c == KEY_RIGHT) {
          id = 1;
          break;
        }
      }
  }
  system("stty cooked");
  return id;
}

static int HumanChoosePlayerInterface(std::vector<int> avail_playerId) {
  assert(!avail_playerId.empty() && "No any available players to be chosen");
  if (avail_playerId.size() == 1) {
    std::cout << "Only one player can be chosen: Player "
              << avail_playerId.back() << std::endl;
    system("pause");
    return avail_playerId.back();
  }

  int playerId;
  while (1) {
    std::cout << "Select a player: (" << avail_playerId.at(0);
    for (auto it = avail_playerId.begin() + 1; it != avail_playerId.end();
         it++) {
      std::cout << ", " << *it;
    }
    std::cout << ")" << std::endl;
    std::cin >> playerId;

    if (std::find(avail_playerId.begin(), avail_playerId.end(), playerId) !=
        avail_playerId.end())
      break;
    std::cout << "Invalid player id: " << playerId << ". ";
  }

  return playerId;
}

Card HumanChooseGuessCardInterface(std::vector<Card> remainCard) {
  int cardId;
  while (1) {
    std::cout << "Select a card: (2-8)" << std::endl;
    std::cin >> cardId;
    if (std::find(remainCard.begin(), remainCard.end(), Card(cardId)) !=
        remainCard.end())
      break;
    std::cout << "Invalid card: " << cardId << ". ";
  }
  return Card(cardId);
}

PlayerAction Human::executeAction(std::vector<int> avail_playerId) {
  assert(handCards.size() == 2 &&
         "Execute an action when holding cards less than 2.");

  std::vector<int> avail_card = getAvailCardId();
  PlayerAction action;

  // Choice.card
  std::cout << "Your turn." << std::endl
            << "Left arrow: " << handCards[0]
            << ", Right arrow: " << handCards[1] << std::endl;
  int id = HumanChooseCardInterface();  // either 0 or 1
  std::cout << "\r";
  action.playCard = handCards.at(id);
  handCards.erase(handCards.begin() + id);

  // Further decision
  if (avail_playerId.empty()) {
    std::cout << "No any available player to be chosen. ";
    system("pause");  // Press any key to continue . . .
    return action;
  }

  switch (action.playCard.getNum()) {
    case 1:
      action.playerId = HumanChoosePlayerInterface(avail_playerId);
      action.guessCard = HumanChooseGuessCardInterface({2, 3, 4, 5, 6, 7, 8});
      break;
    case 2:
    case 3:
    case 5:
    case 6:
      action.playerId = HumanChoosePlayerInterface(avail_playerId);
    default:
      break;
  }
  assert(handCards.size() == 1 && "Two cards remains after execute an action.");
  return action;
}
}  // namespace loveletter