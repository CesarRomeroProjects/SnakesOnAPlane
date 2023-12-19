#include "Plane.hpp"
#include "display.hpp"
#include "rand.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

Plane::Plane(unsigned nRows, unsigned nCols)
: m_rows{nRows}, m_cols{nCols}, m_player{nullptr}, m_nSnakes{0}, m_turns{0}
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        std::cerr << "***** Plane created with invalid size " << nRows << " by "
             << nCols << "!" << std::endl;
        exit(1);
    }
    for (unsigned r = 1; r <= m_rows; r++)
        for (unsigned c = 1; c <= m_cols; c++)
            setCellStatus(r, c, EMPTY);
}

Plane::~Plane()
{
    for (unsigned i{0}; i < m_nSnakes; i++) {
        Snake* snake = m_snakes[i];
        delete snake;
    }

    delete m_player;
}

unsigned Plane::rows() const
{
    return m_rows;
}

unsigned Plane::cols() const
{
    return m_cols;
}

unsigned Plane::snakeCount() const
{
    unsigned numOfAliveSnakes{0};

    // Iterate through every snake (dead or alive), and count
    // the ones that are alive.
    for (unsigned i{0}; i < m_nSnakes; i++) {
        Snake* snake = m_snakes[i];
        if (!snake->isDead())
            numOfAliveSnakes++;
    }
    return numOfAliveSnakes;
}

unsigned Plane::numberOfSnakesAt(unsigned r, unsigned c) const
{
    unsigned numOfSnakes{0};

    // Check if the position is within the plane.
    if (!isPosInBounds(r, c))
        return 0;

    // Check if there is one or more alive snakes at a single position.
    for (unsigned i{0}; i < m_nSnakes; i++) {
        Snake* snake = m_snakes[i];
        if (!snake->isDead() && snake->row() == r && snake->col() == c)
            numOfSnakes++;
    }
    return numOfSnakes;
}

void Plane::moveSnakes()
{
    for (unsigned i{0}; i < m_nSnakes; i++) {
        Snake* snake = m_snakes[i];
        if (!snake->isDead())
            snake->move();
    }
}

void Plane::pushAllSnakes(unsigned r, unsigned c, int dir)
{   
    unsigned adjR{r};
    unsigned adjC{c};

    if (dir == 0) // North
        adjR--;
    else if (dir == 1) // East
        adjC++;
    else if (dir == 2) // South
        adjR++;
    else if (dir == 3) // West 
        adjC--;
    
    for (unsigned i{0}; i < m_nSnakes; i++) {
        Snake* snake = m_snakes[i];
        if (!snake->isDead() && snake->row() == adjR && snake->col() == adjC)
            snake->push(dir);
    }
}

bool Plane::attemptMove(int dir, unsigned& r, unsigned& c)
{
    unsigned newR{r};
    unsigned newC{c};

    if (dir == 0) // North
        newR--;
    else if (dir == 1) // East
        newC++;
    else if (dir == 2) // South
        newR++;
    else if (dir == 3) // West
        newC--;

    if (!isPosInBounds(newR, newC))
        return false;

    r = newR;
    c = newC;
    return true;
}


bool Plane::recommendMove(unsigned r, unsigned c, int& bestDir)
{
    int recommendedDir{-1};
    unsigned minimmumDanger{MAX_SNAKES + 1};

    for (int i{0}; i < NUMDIRS; i++) {
        unsigned newR{r};
        unsigned newC{c};

        if (attemptMove(i, newR, newC)) {
            unsigned danger{computeDanger(newR, newC)};
            if (danger < minimmumDanger) {
                recommendedDir = i;
                minimmumDanger = danger;
            }
        }
    }

    if (recommendedDir != -1) {
        bestDir = recommendedDir;
        return true;
    }
    return false; 
}

Player* Plane::player() const
{
    return m_player;
}

int Plane::getCellStatus(unsigned r, unsigned c) const
{
    checkPos(r, c);
    return m_grid[r-1][c-1];
}

void Plane::display(std::string msg) const
{
    char displayGrid[MAXROWS][MAXCOLS];
    unsigned r, c;
    
      // Fill displayGrid with dots (empty)
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            displayGrid[r-1][c-1] = (getCellStatus(r,c) == EMPTY ? '.' : '*');

        // Indicate each snake's position
    for (unsigned k = 0; k < Plane::MAX_SNAKES; k++)
    {
        const Snake * vp = m_snakes[k];
        if (vp && !vp->isDead()) {
          char& gridChar = displayGrid[vp->row()-1][vp->col()-1];
          switch (gridChar)
          {
            case '.':  gridChar = 'S'; break;
            case 'S':  gridChar = '2'; break;
            case '9':  break;
            default:   gridChar++; break;  // '2' through '8'
          }
        }
    }

      // Indicate player's position
    if (m_player != nullptr)
        displayGrid[m_player->row()-1][m_player->col()-1] = (m_player->isDead() ? 'X' : '@');

      // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            std::cout << displayGrid[r-1][c-1];
        std::cout << std::endl;
    }
    std::cout << std::endl;

      // Write message, snake, and player info
    if (msg != "")
        std::cout << msg << std::endl;

    std::cout << "There are " << snakeCount() << " snakes remaining." << std::endl;
    if (m_player == nullptr)
        std::cout << "There is no player!" << std::endl;
    else if (m_player->isDead())
        std::cout << "The player is dead." << std::endl;
    std::cout << m_turns << " turns have been taken." << std::endl;
}

void Plane::setCellStatus(unsigned r, unsigned c, int status)
{
    checkPos(r, c);
    m_grid[r-1][c-1] = status;
}

bool Plane::addSnake(unsigned r, unsigned c)
{
    if (! isPosInBounds(r, c))
        return false;
    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;
    if (m_nSnakes == MAX_SNAKES)
        return false;
    m_snakes[m_nSnakes] = new Snake(this, r, c);
    m_nSnakes++;
    return true;
}

bool Plane::addPlayer(unsigned r, unsigned c)
{
    if (m_player != nullptr  or  ! isPosInBounds(r, c))
        return false;
    if (numberOfSnakesAt(r, c) > 0)
        return false;
    m_player = new Player(this, r, c);
    return true;
}

bool Plane::isPosInBounds(unsigned r, unsigned c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

void Plane::checkPos(unsigned r, unsigned c) const
{
    if (!isPosInBounds(r, c))
    {
        std::cerr << "***** " << "Invalid plane position (" << r << ","
             << c << ")" << std::endl;
        exit(1);
    }
}

void Plane::turnTaken() { m_turns++; }

unsigned Plane::computeDanger(unsigned r, unsigned c)
{
      // Our measure of danger will be the number of snakes that might move
      // to position r,c.  If a snake is at that position, it is fatal,
      // so a large value is returned.

    if (numberOfSnakesAt(r,c) > 0)
        return MAX_SNAKES+1;

    unsigned danger = 0;
    if (r > 1)
        danger += numberOfSnakesAt(r-1,c);
    if (r < rows())
        danger += numberOfSnakesAt(r+1,c);
    if (c > 1)
        danger += numberOfSnakesAt(r,c-1);
    if (c < cols())
        danger += numberOfSnakesAt(r,c+1);

    return danger;
}
