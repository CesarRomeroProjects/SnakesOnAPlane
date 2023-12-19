#include "Player.hpp"
#include <iostream>

Player::Player(Plane* plane, unsigned r, unsigned c)
:  onWhichPlane{plane}, m_row{r}, m_col{c}, m_dead{false}
{
    if (plane == nullptr)
    {
        std::cerr << "***** The player must be created in some Plane!" << std::endl;
        exit(1);
    }
    if (r < 1  ||  r > plane->rows()  ||  c < 1  ||  c > plane->cols())
    {
        std::cerr << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << std::endl;
        exit(1);
    }
}

unsigned Player::row() const
{
    return m_row;
}

unsigned Player::col() const
{
    return m_col;
}

std::string Player::push()
{
    // Dir{0}: North
    // Dir{1}: East
    // Dir{2}: South
    // Dir{3}: West
    for (int dir{0}; dir < onWhichPlane->NUMDIRS; dir++)
        onWhichPlane->pushAllSnakes(m_row, m_col, dir);
    return "Player pushed.";
}

std::string Player::move(int dir)
{
    // If the player is able to move, then a message is
    // presented to show the location of their movement.
    if (onWhichPlane->attemptMove(dir, m_row, m_col))
    {
        if (onWhichPlane->numberOfSnakesAt(m_row, m_col) > 0)
            return "Player walked into a snake and died.";
        else if (dir == 0)
            return "Player moved north.";
        else if (dir == 1)
            return "Player moved east.";
        else if (dir == 2)
            return "Player moved south.";
        else if (dir == 3)
            return "Player moved west.";
    }
    return "Player couldn't move; player stands.";
}

bool Player::isDead() const
{
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}