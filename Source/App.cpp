#include "App.h"

#include <GL/glut.h>
#include <AR/gsub.h>
#include <AR/video.h>
#include <AR/param.h>

#include <chrono>
#include <iostream>


App::App(const string &configFilePath) : configuration(configFilePath)
{
    printf("Hello\n");

    targetFramerate = stof(configuration["App.targetFramerate"]);
    zBufferSize     = stoi(configuration["App.zBufferSize"]);
    errorThreshold  = stoi(configuration["App.errorThreshold"]);

    finished        = false;
}

App::~App() 
{

}

void App::Run()
{
    beginTime = Clock::now();

    while (!finished) {
        const float elapsedTime = duration_cast<microseconds>
            (Clock::now() - beginTime).count() / 1000000.0f;

        Tick(elapsedTime);

        const Clock::time_point nextFrame = Clock::now()
            + milliseconds(FramerateToFrametime(targetFramerate));

        sleep_until(nextFrame);
    }

    Cleanup();
}

void App::Tick(float elapsedTime)
{
    cout << "Elapsed Time: " << elapsedTime << endl;

    ARUint8        *dataPtr = arVideoGetImage();
    ARMarkerInfo   *markerInfo;

    int             detectedMarkers;

    if (dataPtr == NULL) 
        return;

    argDrawMode2D();
    argDispImage(dataPtr, 0, 0);

    if (arDetectMarker(dataPtr, 100, &markerInfo, &detectedMarkers) < 0) {
        Cleanup();
        throw runtime_error("Error reading camera");
    }

    arVideoCapNext();

    argSwapBuffers();
}

void App::Setup(int argc, char *argv[]) 
{
    glutInit(&argc, argv);

    SetupVideoCapture();

    CreatePatterns();

    arVideoCapStart();
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
    const int   markerCount = stoi(configuration["App.patternCount"]);

    char        sizeKey[50];
    char        pathKey[50];
    char        keySizeX[50];
    char        keySizeY[50];

    for (int i = 0; i < markerCount; i++) {
        sprintf(sizeKey, "Marker.%d.%s", i, "size");
        sprintf(pathKey, "Marker.%d.%s", i, "path");
        sprintf(keySizeX, "Marker.%d.%s", i, "center.x");
        sprintf(keySizeY, "Marker.%d.%s", i, "center.y");

        Center offset = {stod(configuration[keySizeX]), 
            stod(configuration[keySizeY])};

        markers.push_back( 
            Marker(
                configuration[pathKey].c_str(), 
                stod(configuration[sizeKey]), 
                offset
            )
        );
    }
}