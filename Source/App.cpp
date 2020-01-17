/**
 * @file App.cpp
 * @author Roberto Plaza Romero (Roberto.Plaza@alu.uclm.es)
 * @brief Code of the specification found in App.h
 * @version 1.0
 * @date 2020-01-04
 * 
 * @copyright Copyright (c) 2020 GPL v3.0
 * 
 */

#include "App.h"
#include "Colors.h"
#include "MarkerMath.h"

#include <GL/glut.h>
#include <AR/gsub.h>
#include <AR/video.h>
#include <AR/param.h>

App::App(const string &configFilePath) : configuration(configFilePath)
{
    gameMode.SetLives       ( stoi(configuration["GameMode.lives"])     );
    Marker::framesToHidden  = stoi(configuration["App.framesToHidden"]  );

    gameMode.configTime     = stof(configuration["GameMode.configTime"] );
    targetFramerate         = stof(configuration["App.targetFramerate"] );
    zBufferSize             = stoi(configuration["App.zBufferSize"]     );
    errorThreshold          = stoi(configuration["App.errorThreshold"]  );

    finished                = false;

}

App::~App() 
{ 

};

void App::Run()
{
    const float elapsedTime = duration_cast<microseconds>   // const provides a compiler optimization
        (Clock::now() - beginTime).count() / 1000000.0f;

    Tick(elapsedTime);
    
    const Clock::time_point nextFrame = Clock::now() 
        + milliseconds(FramerateToFrametime(targetFramerate));

    sleep_until(nextFrame);
}

void App::Tick(float elapsedTime)
{
    DetectMarkers();

    gameMode.Update(elapsedTime);

    renderer.PrepareNextFrame();

    switch (gameMode.GetGameState())
    {
        case GameState::FindingWalls:
            DrawWallsFromMarker();
            break;

        case GameState::SelectingDifficulty:
            DrawLives();
            DrawWallsFromMemory();
            break;

        case GameState::Playing:
            DrawLives();
            DrawWallsFromMemory();
            break;

        default:
            throw runtime_error("Something went wrong");
            break;
    }

    argSwapBuffers();
}

void App::Setup() 
{
    SetupVideoCapture();
    CreatePatterns();
    arVideoCapStart();

    beginTime = Clock::now();
}

void App::Cleanup() 
{
    arVideoCapStop();
    arVideoClose();
    argCleanup();
}

void App::DetectMarkers()
{
    int             detectedMarkers;
    int             betterMatch;
    int             infoIndex;

    uint32_t        markerIndex;
    ARMarkerInfo   *markerInfo;
    ARUint8        *dataPtr         = arVideoGetImage();


    if (dataPtr == NULL)
    {
        return;
    }

    argDrawMode2D();
    argDispImage(dataPtr, 0, 0);

    if (arDetectMarker(dataPtr, errorThreshold, &markerInfo, &detectedMarkers) < 0) 
    {
        Cleanup();
        throw runtime_error("Error reading camera");
    }

    arVideoCapNext();

    for (markerIndex = 0; markerIndex < markers.size(); markerIndex++) 
    {
        for (infoIndex = 0, betterMatch = -1; infoIndex < detectedMarkers; infoIndex++) 
        {
            if (markers[markerIndex]->GetId() == markerInfo[infoIndex].id) 
            {
                if (betterMatch == -1) 
                {
                    betterMatch = infoIndex;
                }
                
                if (markerInfo[betterMatch].cf < markerInfo[infoIndex].cf) 
                {
                    betterMatch = infoIndex;
                }
            }

            if (betterMatch != -1) 
            {
                markers[markerIndex]->ExtractData(&markerInfo[betterMatch]);
            } 
            else 
            {
                markers[markerIndex]->ExtractData(nullptr);
            }
        }
    }
}

void App::SetupVideoCapture() 
{
    ARParam windowParam;
    ARParam cameraParam;

    int cameraSizeX;
    int cameraSizeY;

    char videoInput[50];
    sprintf(videoInput, "-dev=%s", configuration["App.camera"].c_str());

    if (arVideoOpen(videoInput) < 0)
    {
        throw std::runtime_error("Impossible to initialize ARToolkit video.");
    }

    if (arVideoInqSize(&cameraSizeX, &cameraSizeY) < 0)
    {    
        throw std::runtime_error("Impossible to get camera size");
    }

    if (arParamLoad(configuration["App.cameraConfigPath"].c_str(), 1, &windowParam) < 0)
    {    
        throw std::runtime_error("Impossible to start camera recording");
    }

    arParamChangeSize(&windowParam, cameraSizeX, cameraSizeY, &cameraParam);
    arInitCparam(&cameraParam);
    argInit(&cameraParam, 1.0, 0, 0, 0, 0);
}

void App::CreatePatterns()
{
    char            wallMarkerPath[50];
    
    const int       wallCount       =   stod(configuration["Marker.wall.count"      ]);
    const double    wallMarkerSize  =   stod(configuration["Marker.wall.size"       ]);
    const double    wallMarkerDispX =   stod(configuration["Marker.wall.center.x"   ]);
    const double    wallMarkerDispY =   stod(configuration["Marker.wall.center.y"   ]);

    for (int i = 0; i < wallCount; i++) 
    {
        sprintf(wallMarkerPath, "Marker.wall.%d.path", i);

        markers.push_back
        (
            make_shared<Marker>
            (
                configuration[wallMarkerPath].c_str(),
                wallMarkerSize,
                wallMarkerDispX,
                wallMarkerDispY
            )
        );

        gameMode.wallMarkers.push_back(markers.back());
   
        wallPositions.push_back({0.0, 0.0, 0.0});
    }

    markers.push_back
    (
        make_shared<Marker>
        (
            configuration       ["Marker.config.path"].c_str(),
            stod(configuration  ["Marker.config.size"       ]),
            stod(configuration  ["Marker.config.center.y"   ]),
            stod(configuration  ["Marker.config.center.x"   ])
        )
    );

    gameMode.configMarker = markers.back();

    markers.push_back
    (
        make_shared<Marker> 
        (
            configuration       ["Marker.shield.path"].c_str(),
            stod(configuration  ["Marker.shield.size"       ]),
            stod(configuration  ["Marker.shield.center.y"   ]),
            stod(configuration  ["Marker.shield.center.x"   ])
        )
    );

    gameMode.shieldMarker = markers.back();
}

void App::DrawWallsFromMarker()
{
    const uint32_t wallMarkers = stod(configuration["Marker.wall.count"]);

    for (uint32_t i = 0; i < wallMarkers; i++) 
    { 
        const uint32_t j = (i + 1) % wallMarkers;

        if (markers[i]->IsVisible() 
            && 
            markers[j]->IsVisible())
        {
            const double    length  = (MarkerMath::Distance(
                markers[i]->GetLocation(), markers[j]->GetLocation()) + 
                markers[i]->GetSize()) * 2 / markers[i]->GetSize() ;
            
            double          angle   = MarkerMath::GetRoll(
                markers[i]->GetLocation(), 
                markers[j]->GetLocation()
            );

            switch (i)
            {   /* Done */
                case 0:
                    angle = - 90 - angle;
                    break;
                
                case 1:
                    angle = - 90 - angle;
                    break;
                /* Done */
                case 2:
                    angle = - 90 - angle;
                    break;
                /* Done */
                case 3:
                    angle = -angle + 180;
                    break;
            }

            wallPositions[i] = markers[i]->GetGlTransMat();

            renderer.BufferTransform(markers[i]->GetGlTransMat());
            renderer.DrawWall(angle, length, markers[i]->GetSize()/2);
        }
    }
}

void App::DrawWallsFromMemory()
{
    for (uint32_t wallIndex = 0; wallIndex < wallPositions.size(); wallIndex++)
    {

    }
}

void App::DrawLives()
{
    if (markers[4]->IsVisible())
    {
        renderer.BufferTransform(markers[4]->GetGlTransMat());

        glTranslated(32.0, 0.0, 0.0);

        for (int i = 0; i < gameMode.GetMaxLives(); i++)
        {
            glTranslated(-16.0, 0.0, 0.0);

            if (i < gameMode.GetLives())
            {
                renderer.DrawWholeCircle();
            }
            else
            {
                renderer.DrawEmptyCircle();
            }
        }
    }
}