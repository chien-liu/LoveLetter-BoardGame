#include "player.h"

#include <assert.h>

#include <algorithm>
#include <iostream>
#include <random>

#include "card.h"
using namespace std;

Player::Player(bool ai) : AI(ai) {
  alive = true;
  invincible = false;
}

void Player::draw(Card card) {
  if (hand.getNum()) {
    tmp_card = card;
  } else {
    hand = card;
  }
}

Choice Player::chooseCard(vector<int> avail_card, vector<int> avail_player) {
  assert(tmp_card != Card(0));
  assert(avail_card.size() > 0);
  assert(avail_player.size() > 0);

  // Choice.card
  Choice choice = {Card(0), -1, Card(0)};
  int card_desision;
  random_shuffle(avail_card.begin(), avail_card.end());
  card_desision = avail_card.back();
  if (!AI) {  // human player
    do {
      cout << "Choose a card 0(" << hand.getName() << ") 1("
           << tmp_card.getName() << ")" << endl;
      cin >> card_desision;
    } while (card_desision != 0 && card_desision != 1);
  }
  if (card_desision) {  // 1
    choice.card = tmp_card;
    tmp_card = Card(0);
  } else {  // 0
    choice.card = hand;
    hand = tmp_card;
    tmp_card = Card(0);
  }

  // Further decision
  if (AI) {
    random_shuffle(avail_player.begin(), avail_player.end());
  }
  switch (choice.card.getNum()) {
    case 1:
      if (AI) {
        choice.player_id = avail_player.back();
        choice.guess = Card(rand() % 7 + 2);
      } else {
        cout << "Select a player: (";
        for (auto i : avail_player) {
          cout << i << ", ";
        }
        cout << ")" << endl;
        cin >> choice.player_id;

        cout << "Select a card: (2-8)" << endl;
        int id;
        cin >> id;
        choice.guess = Card(id);
      }
      break;
    case 2:
    case 3:
    case 5:
    case 6:
      if (AI) {
        choice.player_id = avail_player.back();
      } else {
        cout << "Select a player: (";
        for (auto i : avail_player) {
          cout << i << ", ";
        }
        cout << ")" << endl;
        cin >> choice.player_id;
      }
      break;
    case 4:
      break;
    case 7:

      break;
    case 8:

      break;
    default:
      break;
  }
  assert(tmp_card == Card(0));
  return choice;
}