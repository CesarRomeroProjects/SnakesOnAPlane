#include <cstdlib>
#include <ctime>
#include "Game.hpp"

int main()
{
      // Initialize the random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Create a game
    // Use this instead to create a mini-game:   
    // Game g(3, 5, 2);
    Game g(3, 5, 2);

      // Play the game
    g.play();
}

