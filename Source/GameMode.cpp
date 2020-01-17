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

#include <GL/gl.h>

#include <iostream>


GameMode::GameMode(int lives)
    : maxLives(lives)
{
    gameState       = GameState::FindingWalls;
    currentLives    = maxLives;
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
    if (!configMarker->HasBeenHidden()) 
    {
        difficulty = configMarker->GetRoll();
        timeStamp = elapsedTime;
        cout << "Difficulty: " << difficulty << endl;
    } 
    else 
    {
        if ((elapsedTime - timeStamp) >= configTime) 
        {
            cout << "Starting game." << endl;
            gameState = GameState::Playing;
        }
    }
}

void GameMode::Play(float elapsedTime)
{

}
