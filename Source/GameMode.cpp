/**
 * @file GameMode.cpp
 * @author Roberto Plaza Romero (Roberto.Plaza@alu.uclm.es)
 * @brief Implementation of the specification in GameMode.h
 * @version 1.0
 * @date 2020-01-04
 * 
 * @copyright Copyright (c) 2020 GPL v3.0
 * 
 */

#include "GameMode.h"
#include "App.h"

#include <GL/gl.h>

#include <iostream>


GameMode::GameMode(App *app, int lives)
    : maxLives(lives), application(app)
{
    gameState       = GameState::FindingWalls;
    currentLives    = maxLives;
    nextObjective   = -1;
}

GameMode::~GameMode()
{

}

GameState GameMode::GetGameState() const 
{
    return gameState;
}

void GameMode::SetLives(int newLives)
{
    maxLives        = newLives;
    currentLives    = maxLives;
}

int GameMode::GetMaxLives() const
{
    return maxLives;
}

int GameMode::GetLives() const 
{
    return currentLives;
}

int GameMode::GetTargetWall() const
{
    return nextObjective;
}

void GameMode::Update(float elapsedTime)
{
    switch (gameState) 
    {
        case GameState::FindingWalls: 
            FindWalls(elapsedTime); 
            break;

        case GameState::SelectingDifficulty: 
            SelectDifficulty(elapsedTime); 
            break;

        case GameState::Playing:
            Play(elapsedTime);
            break;

        default:
            gameState = GameState::FindingWalls;
            break;
    }
}

void GameMode::FindWalls(float elapsedTime)
{
    uint32_t visibleMarkers = 0;

    for (const auto &wallMarker : wallMarkers)
    {
        if (wallMarker->IsVisible())
        {
            visibleMarkers++;
        }
    }

    if (configMarker->IsVisible())
    {
        visibleMarkers++;
    }

    if (shieldMarker->IsVisible())
    {
        visibleMarkers++;
    }

    if (visibleMarkers >= wallMarkers.size() + 2) 
    {
        cout << "Selected difficulty:" << endl;
        gameState = GameState::SelectingDifficulty;
        timeStamp = elapsedTime;
    }
}

void GameMode::SelectDifficulty(float elapsedTime)
{
    if (!configMarker->HasBeenHidden() && configMarker->IsVisible()) 
    {
        timeToCarryOnAction = configMarker->GetRoll();
        timeStamp           = elapsedTime;
        cout << "Difficulty: " << timeToCarryOnAction << endl;
    } 
    else 
    {
        if ((elapsedTime - timeStamp) >= configTime) 
        {
            static const double maxRoll = 180.0;
            static const double maxTime = 5.0;

            cout << "Starting game." << endl;

            timeToCarryOnAction = (maxRoll - timeToCarryOnAction) / maxRoll // Proportion
                * maxTime; 
            timeStamp           = -1.0f;
            gameState           = GameState::Playing;
        }
    }
}

void GameMode::Play(float elapsedTime)
{
    if (timeStamp == -1.0f)             // No objective defined
    {
        timeStamp       = elapsedTime + timeToCarryOnAction;
        nextObjective   = rand() % 4;
    }
    else if (elapsedTime > timeStamp)   // Player has failed to carry on action
    {
        cout << "You lost a life. Be faster next time." << endl;
        timeStamp       = -1.0f;
        currentLives--;
        
        if (currentLives <= 0)
        {
            cout << "Thank you for playing, you lost" << endl;
            gameState = GameState::GameLost;
        }
    }
    else                                // Check if the player has done it correctly
    {
        if (this->IsPlayerSuccessful())
        {
            score++;
            cout << "Well done, your current score is: " << score << endl;
            timeStamp = -1.0f;
        }
    }
}

bool GameMode::IsPlayerSuccessful()
{
    const Vector    shieldPosition  = shieldMarker->GetLocation();

    switch (nextObjective)
    {
        case 0:
            return application->IsAtTheTopOfTheWall(shieldPosition);
            break;
        
        case 1:
            return application->IsAtTheRightOfTheWall(shieldPosition);
            break;

        case 2:
            return application->IsAtTheBottomOfTheWall(shieldPosition);
            break;

        case 3:
            return application->IsAtTheLeftOfTheWall(shieldPosition);
            break;

        default:
            throw runtime_error("Inconsistent objective");
            break;
    }

    return false;
}