#include "App.h"

#include <GL/glut.h>
#include <AR/gsub.h>
#include <AR/video.h>
#include <AR/param.h>

#include <chrono>
#ifdef DEBUG
    #include <iostream>
#endif

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
    beginTime = Clock::now();

    while (!finished) {
        const Clock::time_point nextFrame = Clock::now()
            + milliseconds(FramerateToFrametime(targetFramerate));
        
        const float elapsedTime = duration_cast<microseconds>
            (Clock::now() - beginTime).count() / 1000000.0f;

        Tick(elapsedTime);
        sleep_until(nextFrame);
    }

    Cleanup();
}

void App::Tick(float elapsedTime)
{
    #ifdef DEBUG
        cout << "Elapsed Time: " << elapsedTime << endl;
    #endif // DEBUG

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

    for (auto &marker : markers) {
        marker.DetectYourself(&markerInfo, detectedMarkers);
        if (marker.IsVisible()) {
            glLoadMatrixd(marker.GetGlTransMat().data());
            //glTranslatef(0.0, 0.0, 60.0);
            //;
            marker.DrawModel();
        #ifdef DEBUG
            const double distance = marker.DistanceToCamera();
            cout << "Distance to camera: " <<  distance << endl;
            cout << "Rotation of the Marker: " << marker.GetRoll() << endl;
        #endif
        }
    }
    argSwapBuffers();
}

void App::Setup() 
{
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
    const int   markerCount = stoi(configuration["App.patternCount"]);

    char        sizeKey[50];
    char        pathKey[50];
    char        keySizeX[50];
    char        keySizeY[50];

    markers.reserve(markerCount);

    for (int i = 0; i < markerCount; i++) {
        sprintf(sizeKey, "Marker.%d.%s", i, "size");
        sprintf(pathKey, "Marker.%d.%s", i, "path");
        sprintf(keySizeX, "Marker.%d.%s", i, "center.x");
        sprintf(keySizeY, "Marker.%d.%s", i, "center.y");

        markers.push_back( 
            Marker(
                configuration[pathKey].c_str(), 
                stod(configuration[sizeKey]), 
                stod(configuration[keySizeX]),
                stod(configuration[keySizeY])
            )
        );

        markers.back().DrawModel = std::bind(&Renderer::DrawTeapot, renderer);
    }

    #ifdef DEBUG
        cout << "Size of markers: " << markers.size() << endl;
    #endif // DEBUG
}