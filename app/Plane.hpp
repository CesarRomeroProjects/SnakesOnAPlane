#ifndef _PLANE_HPP
#define _PLANE_HPP

#include "Player.hpp"
#include "Snake.hpp"
#include <string>

class Player; // this is called a "forward declaration."  For purposes of project 1 in ICS 45C, don't worry about this line.
class Snake; // see last line's comment.

class Plane {
public:

  constexpr static int EMPTY = 0;
  constexpr static unsigned MAXROWS = 20; // max number of rows in the plane
  constexpr static unsigned MAXCOLS = 20; // max number of columns in the plane
  constexpr static unsigned MAX_SNAKES = 100; // max number of snakes allowed

  constexpr static int NORTH = 0;
  constexpr static int EAST = 1;
  constexpr static int SOUTH = 2;
  constexpr static int WEST = 3;
  constexpr static int NUMDIRS = 4;

  // Constructor/destructor
  Plane(unsigned nRows, unsigned nCols);
  ~Plane();

  // Accessors
  unsigned rows() const;
  unsigned cols() const;
  Player *player() const;
  unsigned snakeCount() const;
  int getCellStatus(unsigned r, unsigned c) const;
  unsigned numberOfSnakesAt(unsigned r, unsigned c) const;
  void display(std::string msg) const;

  // Mutators
  void setCellStatus(unsigned r, unsigned c, int status);
  bool addSnake(unsigned r, unsigned c);
  bool addPlayer(unsigned r, unsigned c);
  void moveSnakes();
  void
  pushAllSnakes(unsigned r, unsigned c,
                int dir); // pushes all snakes at [r,c] in the given direction
  bool attemptMove(int dir, unsigned &r, unsigned &c);
  bool recommendMove(unsigned r, unsigned c, int &bestDir);
  unsigned computeDanger(unsigned r, unsigned c);

  void turnTaken();

private:
  int m_grid[MAXROWS][MAXCOLS];
  unsigned m_rows;
  unsigned m_cols;
  Player *m_player;
  Snake *m_snakes[MAX_SNAKES];
  unsigned m_nSnakes;
  unsigned m_turns;

  // Helper functions
  void checkPos(unsigned r, unsigned c) const;
  bool isPosInBounds(unsigned r, unsigned c) const;
};

#endif