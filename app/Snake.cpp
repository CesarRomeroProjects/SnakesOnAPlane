#include "Snake.hpp"
#include "rand.hpp"
#include <iostream>

Snake::Snake(Plane* plane, unsigned r, unsigned c)
: onWhichPlane{plane}, m_row{r}, m_col{c}, m_dead{false}
{
    if (plane == nullptr)
    {
        std::cerr << "***** A snake must be created in some plane!" << std::endl;
        exit(1);
    }
    if (r < 1  ||  r > plane->rows()  ||  c < 1  ||  c > plane->cols())
    {
        std::cerr << "***** Snake created with invalid coordinates (" << r << ","
             << c << ")!" << std::endl;
        exit(1);
    }
}

unsigned Snake::row() const
{
    return m_row;
}

unsigned Snake::col() const
{
    return m_col;
}

bool Snake::isDead() const
{
    return m_dead;
}

void Snake::move()
{
    // A random number generator between 0 and 3, which either one of those
    // decide the direction the snake(s) will move.
    int randomDir{randInt(0, 3)};

    unsigned newR{m_row};
    unsigned newC{m_col};


    // The snake attempts to move into their new position.
    // If the snake is going to be out of bounds, it will not move.
    if (onWhichPlane->attemptMove(randomDir, newR, newC)) {
        m_row = newR;
        m_col = newC;

        // Once the snake has moved, if it is touching a player, then the player is killed.
        if (m_row == onWhichPlane->player()->row() && m_col == onWhichPlane->player()->col())
            onWhichPlane->player()->setDead();
    }
}

void Snake::setDead()
{
    m_dead = true;
}  

void Snake::push(int dir)
{
    unsigned newR{m_row};
    unsigned newC{m_col};

    if (! onWhichPlane->attemptMove(dir, newR, newC)) {
        m_row = newR;
        m_col = newC;
        setDead();
    } else if (dir == 0)
        m_row--;
    else if (dir == 1)
        m_col++;
    else if (dir == 2)
        m_row++;
    else if (dir == 3)
        m_col--;
}