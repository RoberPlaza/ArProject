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

#include <GL/glut.h>
#include <AR/gsub.h>
#include <AR/video.h>
#include <AR/param.h>

App::App(const string &configFilePath) : configuration(configFilePath)
{
    targetFramerate = stof(configuration["App.targetFramerate"]);
    zBufferSize     = stoi(configuration["App.zBufferSize"]);
    errorThreshold  = stoi(configuration["App.errorThreshold"]);

    finished        = false;
}

App::~App() { };

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
    int             detectedMarkers;

    ARMarkerInfo   *markerInfo;
    ARUint8        *dataPtr         = arVideoGetImage();


    if (dataPtr == NULL)  return;

    argDrawMode2D();
    argDispImage(dataPtr, 0, 0);

    if (arDetectMarker(dataPtr, errorThreshold, &markerInfo, &detectedMarkers) < 0) {
        Cleanup();
        throw runtime_error("Error reading camera");
    }

    arVideoCapNext();

    argDrawMode3D();
    argDraw3dCamera(0, 0);

    renderer.PrepareNextFrame();

    for (auto &marker : markers)
        marker->DetectYourself(&markerInfo, detectedMarkers);
    
    gameMode.Update(elapsedTime);

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

void App::SetupVideoCapture() 
{
    ARParam windowParam;
    ARParam cameraParam;

    int cameraSizeX;
    int cameraSizeY;

    char videoInput[17];
    sprintf(videoInput, "-dev=%s", configuration["camera"].c_str());

    if (arVideoOpen(videoInput) < 0)
        throw std::runtime_error("Impossible to initialize ARToolkit video.");

    if (arVideoInqSize(&cameraSizeX, &cameraSizeY) < 0)
        throw std::runtime_error("Impossible to get camera size");

    if (arParamLoad(configuration["App.cameraConfigPath"].c_str(), 1, &windowParam) < 0)
        throw std::runtime_error("Impossible to start camera recording");

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

    for (int i = 0; i < wallCount; i++) {
        sprintf(wallMarkerPath, "Marker.wall.%d.path", i);

        markers.push_back(
            make_shared<Marker>(
                configuration[wallMarkerPath].c_str(),
                wallMarkerSize,
                wallMarkerDispX,
                wallMarkerDispY
            )
        );

        gameMode.wallMarkers.push_back(markers.back());
    }

    markers.push_back(
        make_shared<Marker>(
            configuration       ["Marker.config.path"].c_str(),
            stod(configuration  ["Marker.config.size"       ]),
            stod(configuration  ["Marker.config.center.y"   ]),
            stod(configuration  ["Marker.config.center.x"   ])
        )
    );

    gameMode.configMarker = markers.back();

    markers.push_back(
        make_shared<Marker> (
            configuration       ["Marker.shield.path"].c_str(),
            stod(configuration  ["Marker.shield.size"       ]),
            stod(configuration  ["Marker.shield.center.y"   ]),
            stod(configuration  ["Marker.shield.center.x"   ])
        )
    );

    gameMode.shieldMarker = markers.back();
}