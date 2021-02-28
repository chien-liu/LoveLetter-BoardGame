#include "loveletter.h"

#include <assert.h>
#include <time.h>

#include <algorithm>  // std::random_shuffle
#include <random>
#include <string>
#include <vector>

using namespace std;

LoveLetter::LoveLetter(int n) : n_player(n), pool(n_player) {
  srand(time(NULL));
  round = 1;
  // Initialize players
  current_player = rand() % n_player;
  terminate = false;
  Player p(false);
  p.draw(pool.next());
  players.push_back(p);
  for (int i = 1; i < n_player; i++) {
    Player p(true);
    p.draw(pool.next());
    players.push_back(p);
  }
}

void LoveLetter::drawCard() { players[current_player].draw(pool.next()); }

void LoveLetter::printPlayer() {
  string c[4] = {};
  for (int i = 0; i < 4; i++) {
    if (players[i].alive) {
      if (players[i].invincible) {
        c[i] = "\u0394";
      } else {
        c[i] = "O";
      }
    } else {
      c[i] = "X";
    }
  }
  cout << "---------------------" << endl
       << "\tRound:" << round << endl
       << "\tp2:" << c[2] << endl
       << "p1:" << c[1] << "\t\t"
       << "p3:" << c[3] << endl
       << "\tp0:" << c[0] << endl;
}

void LoveLetter::action() {
  vector<int> avail_card, avail_player;
  // available card
  Player& p = players[current_player];
  avail_card = {0, 1};
  if (p.showHand() == Card(7)) {
    if (p.showTmp() == Card(5) || p.showTmp() == Card(6)) {
      avail_card = {0};
    }
  } else if (p.showTmp() == Card(7)) {
    if (p.showHand() == Card(5) || p.showHand() == Card(6)) {
      avail_card = {1};
    }
  }
  // available people
  for (int i = 0; i < n_player; i++) {
    if ((players[i].alive) && (i != current_player) &&
        !(players[i].invincible)) {
      avail_player.push_back(i);
    }
  }
  if (avail_player.size() == 0) {
    avail_player.push_back(current_player);
  }

  choice = players[current_player].chooseCard(avail_card, avail_player);
}

void LoveLetter::update() {
  cout << "[Game Info] Player" << current_player << " use "
       << choice.card.getName() << "(" << choice.card.getNum() << ")" << endl;
  players[current_player].invincible = false;
  switch (choice.card.getNum()) {
    case 1:
      cout << "[Game Info] Target Player" << choice.player_id << endl;
      cout << "[Game Info] Guess card " << choice.guess.getName() << "("
           << choice.card.getNum() << ")" << endl;
      if (players[choice.player_id].showHand() == choice.guess) {
        players[choice.player_id].alive = false;
      }
      break;
    case 2:
      cout << "[Game Info] Target Player" << choice.player_id << endl;
      cout << "[Game Info] Player" << choice.player_id << "'s card is "
           << players[choice.player_id].showHand().getName() << endl;
      break;
    case 3:
      cout << "[Game Info] Target Player" << choice.player_id << endl;
      if (players[current_player].showHand() >
          players[choice.player_id].showHand()) {
        players[choice.player_id].alive = false;
      } else if (players[current_player].showHand() <
                 players[choice.player_id].showHand()) {
        players[current_player].alive = false;
      }
      break;
    case 4:
      players[current_player].invincible = true;
      break;
    case 5:
      cout << "[Game Info] Target Player" << choice.player_id << endl;
      players[choice.player_id].discard();
      if (pool.count() > 0) {
        players[choice.player_id].draw(pool.next());
      } else {
        players[choice.player_id].draw(pool.specialDraw());
      }
      break;
    case 6: {
      cout << "[Game Info] Target Player" << choice.player_id << endl;
      Card tmp = players[choice.player_id].showHand();
      players[choice.player_id].discard();
      players[choice.player_id].draw(players[current_player].showHand());
      players[current_player].discard();
      players[current_player].draw(tmp);
      break;
    }
    case 7:
      break;
    case 8:
      players[current_player].alive = false;
      break;

    default:
      break;
  }

  // update index of next player
  int start = current_player;
  do {
    current_player++;
    if (current_player >= n_player) {
      current_player = 0;
    }
  } while (!players[current_player].alive);

  // update round counter
  round++;
}

void LoveLetter::checkEnd() {
  if (!pool.count()) {
    terminate = true;
    cout << "Game end: Card pool is out of cards." << endl;
    return;
  }
  int count = 0;
  for (auto p : players) {
    count += p.alive;
  }
  assert(count && "Error: All player dead.");
  if (count == 1) {
    terminate = true;
    cout << "Game end: Last player survived." << endl;
    return;
  }
}

void LoveLetter::updateWinner() {
  winner = -1;
  Card card;  // 0
  cout << "------------------" << endl;
  cout << "Player\tCard" << endl;
  for (size_t i = 0; i < players.size(); i++) {
    assert(players[i].oneCard());
    if (players[i].alive) {
      cout << i << "\t" << players[i].showHand().getName() << "("
           << players[i].showHand().getNum() << ")" << endl;
      if (players[i].showHand() > card) {
        winner = i;
        card = players[i].showHand();
      }
    }
  }
}