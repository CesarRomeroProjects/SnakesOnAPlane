#ifndef _SNAKE_HPP
#define _SNAKE_HPP

#include "Plane.hpp"

class Plane;

class Snake
{
  public:
      // Constructor:  on which plane does this Snake live, and in which row/column is it starting?
    Snake(Plane* plane, unsigned r, unsigned c);

      // Accessors
    unsigned  row() const;
    unsigned  col() const;
    bool isDead() const;
    

      // Mutators
    void move();
    void setDead();
    void push(int dir); // pushes this snake in this direction.

  private:
    Plane* onWhichPlane;
    unsigned    m_row;
    unsigned    m_col;
    bool        m_dead;
};

#endif