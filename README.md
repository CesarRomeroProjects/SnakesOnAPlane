# Project 1: Snakes on the Plane

# Overview
Welcome to the world of "Snakes on the Plane," a new video game under development where you navigate a flat, two-dimensional environment filled with snakes. Your goal is to survive by strategically moving and pushing snakes off the plane. This prototype uses character-based graphics and requires you to implement various functions in the provided skeleton code.

# Game Rules
- You control a player on a 2D plane inhabited by snakes.
- Each turn, you choose an action: move one step or attempt to push nearby snakes without moving.
- Snakes move randomly one step in any direction each turn.
- If a snake moves onto the player's position, the player dies.
- If the player moves onto a snake's position, the player dies.
- Pushing a snake off the plane causes its demise.
- The game ends when either the player or all snakes are dead.

# Actions
1. Move:
    - Move one step north (n), east (e), south (s), or west (w).
    - If attempting to move out of the plane boundaries, no movement occurs.
    - If moving onto a snake's position, the player dies.
2. Push:
    - Push nearby snakes one block further away.
    - If pushing would cause a snake to leave the plane, the snake perishes.
    - A snake is considered dead if its m_dead field is set to true.

# Computer Reccomendations
- If you press Enter, the computer recommends the move based on the situation:
    - If snakes surround the player, it suggests pushing.
    - If an empty spot exists, it recommends moving there.
    - If multiple empty spots, it suggests the square with the lowest danger factor (computed by Plane::computeDanger()).

# Classes and Responsibilities

# Game
- Create a game with specified rows, columns, and snakes.
- Play the game.

# Plane
- Create a plane with no occupied positions.
- Create snakes and a player at specified positions.
- Move snakes on the plane.
- Provide information about the plane (size, snake count, living snakes).
- Display the plane's status.

# Player
- Create a player at a specific position.
- Move in a direction or push snakes.
- Report death status and position.

# Snake
- Create a snake at a specific position.
- Move randomly in one of four directions.
- Report death status and position.

# Implementation Guidelines
- Implement the required functions outlined in Plane.cpp, Player.cpp, and Snake.cpp.
- Do not modify the contents of display.cpp.
- You may make changes to the private parts of the classes but not the public interface.
- You may add global constants if needed.
- Do not use the word "friend" in your program.
