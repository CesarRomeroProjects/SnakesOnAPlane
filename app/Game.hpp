#ifndef _GAME_HPP
#define _GAME_HPP

#include "Plane.hpp"

class Plane;

class Game {
public:
  // Constructor/destructor
  Game(unsigned rows, unsigned cols, unsigned nSnakes);
  ~Game();

  // Mutators
  void play();

private:
  Plane *m_plane;

  // Helper functions
  std::string takePlayerTurn();
  static bool charToDir(char ch, int &dir);
};

#endif