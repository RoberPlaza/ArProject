/**
 * @file GameMode.h
 * @author Roberto Plaza Romero (Roberto.Plaza@alu.uclm.es)
 * @brief This file contains the specification of the game mode.
 * @version 1.0
 * @date 2020-01-04
 * 
 * @copyright Copyright (c) 2020 GPL v3.0
 * 
 */

#ifndef GAME_MODE__
#define GAME_MODE__


#include "Marker.h"
#include "Common.h"

#include <vector>


/**
 * @brief Enum used to implement a State pattern in the GameMode Class
 * 
 */
enum class GameState : uint8_t
{
    FindingWalls,           // The game is trying to find the walls of the board.
    SelectingDifficulty,    // Selecting the difficulty.
    Playing,                // Game is playing.
    Error,                  // Unwanted state.
    MAX                     // Enum encouraged practice.
};

/**
 * @brief Enum used to access the different markers of the wall.
 * 
 */
enum class WallPositions : uint8_t
{ 
    TopLeft     = 0,
    TopRight    = 1,
    BottomLeft  = 2,
    BottomRight = 3,
    MAX         = 4
};


/**
 * @brief Class to carry on a match of this game.
 * 
 * The logic of the match is carry on by this class. 
 * It also contains the variables needed to carry on 
 * that logic. It's not duty of this class to update the 
 * position of the markers or calculate the distance 
 * between them.
 * 
 */
class GameMode
{
public:

    /**
     * @brief Construct a new Game Mode object
     * 
     */
    GameMode ();

    /**
     * @brief Destroy the Gamemode object
     * 
     */
    virtual ~GameMode ();

    /**
     * @brief Updates the game mode.
     * 
     * @param elapsedTime Time since the begining of the match in seconds.
     */
    virtual void Update(float elapsedTime);

    /**
     * @brief Set the Lives of the player.
     * 
     * @param newLives How many lives the user has.
     */
    void SetLives(int newLives);

private:

    /**
     * @brief Tries to find the four walls of the match.
     * 
     * @param elapsedTime Time (in seconds) since the beginning of the game
     */
    void FindWalls(float elapsedTim);

    /**
     * @brief Sets a difficulty for the game session.
     * 
     * @param elapsedTime Time (in seconds) since the beginning of the game
     */
    void SelectDifficulty(float elapsedTime);

    /**
     * @brief Main loop of the game.
     * 
     * @param elapsedTime Time (in seconds) since the beginning of the game
     */
    void Play(float elapsedTime);

public:

    /**
     * @brief Markers used to set the walls of the aplication.
     * 
     */
    vector<ArMarker> wallMarkers;

    /**
     * @brief Marker that represents the shield.
     * 
     */
    ArMarker        shieldMarker;

    /**
     * @brief Speed configuration marker.
     * 
     */
    ArMarker        configMarker;

    /**
     * @brief Number of seconds to wait in order to start the game
     * and stop configuring the application.
     * 
     */
    float           configTime;

    /**
     * @brief Times the user can fail before the game ends.
     * 
     */
    int             currentLives;

private:

    /**
     * @brief State of the game.
     * 
     */
    GameState       gameState;

    /**
     * @brief Variable used to store different timestamps through the 
     * development of the game.
     * 
     */
    float           timeStamp;

    /**
     * @brief Difficulty of the game.
     * 
     */
    double          difficulty;

};


#endif // !GAME_MODE__