#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include "Plane.hpp"
#include <string>

class Plane; // this is called a "forward declaration."  For purposes of project 1 in ICS 45C, don't worry about this line.

class Player
{
  public:
      // Constructor
    Player(Plane *plane, unsigned r, unsigned c);

      // Accessors
    unsigned  row() const;
    unsigned  col() const;
    bool isDead() const;

      // Mutators
    std::string move(int dir);
    std::string push();
    void   setDead();

  private:
    Plane* onWhichPlane;
    unsigned    m_row;
    unsigned    m_col;
    bool   m_dead;
};

#endif