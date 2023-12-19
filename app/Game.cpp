#include "Game.hpp"
#include "rand.hpp"
#include <iostream>

Game::Game(unsigned rows, unsigned cols, unsigned nSnakes) {
  if (nSnakes < 0 or nSnakes > Plane::MAX_SNAKES) {
    std::cerr << "***** Game created with invalid number of snakes:  "
              << nSnakes << std::endl;
    exit(1);
  }
  int nEmpty = rows * cols - nSnakes - 1; // 1 for Player
  if (nEmpty < 0) {
    std::cerr << "***** Game created with a " << rows << " by " << cols
              << " plane, which is too small too hold a player and " << nSnakes
              << " snakes!" << std::endl;
    exit(1);
  }

  // Create Plane
  m_plane = new Plane(rows, cols);

  // Add player
  int rPlayer;
  int cPlayer;
  do {
    rPlayer = randInt(1, rows);
    cPlayer = randInt(1, cols);
  } while (m_plane->getCellStatus(rPlayer, cPlayer) != Plane::EMPTY);
  m_plane->addPlayer(rPlayer, cPlayer);

  // Populate with snakes
  while (nSnakes > 0) {
    int r = randInt(1, rows);
    int c = randInt(1, cols);
    if (r == rPlayer && c == cPlayer)
      continue;
    m_plane->addSnake(r, c);
    nSnakes--;
  }
}

Game::~Game() { delete m_plane; }

std::string Game::takePlayerTurn() {
  for (;;) {
    m_plane->turnTaken();
    std::cout << "Your move (n/e/s/w/p or nothing): ";
    std::string playerMove;
    getline(std::cin, playerMove);

    Player *player = m_plane->player();
    int dir;

    if (playerMove.size() == 0) {
      if (m_plane->recommendMove(player->row(), player->col(), dir))
        return player->move(dir);
      else
        return player->push();
    } else if (playerMove.size() == 1) {
      if (tolower(playerMove[0]) == 'p')
        return player->push();
      else if (charToDir(playerMove[0], dir))
        return player->move(dir);
    }
    std::cout << "Player move must be nothing, or 1 character n/e/s/w/p."
              << std::endl;
  }
}

void Game::play() {
  m_plane->display("");
  while (!m_plane->player()->isDead() && m_plane->snakeCount() > 0) {
    std::string msg = takePlayerTurn();
    Player *player = m_plane->player();
    if (player->isDead())
      break;
    m_plane->moveSnakes();
    m_plane->display(msg);
  }
  if (m_plane->player()->isDead())
    std::cout << "You lose." << std::endl;
  else
    std::cout << "You win." << std::endl;
}

bool Game::charToDir(char ch, int &dir) {
  switch (tolower(ch)) {
  default:
    return false;
  case 'n':
    dir = Plane::NORTH;
    break;
  case 'e':
    dir = Plane::EAST;
    break;
  case 's':
    dir = Plane::SOUTH;
    break;
  case 'w':
    dir = Plane::WEST;
    break;
  }
  return true;
}