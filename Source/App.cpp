#include "App.h"

#include <AR/gsub.h>
#include <AR/video.h>
#include <AR/param.h>

#include <GL/glut.h>

#include <chrono>
#include <iostream>


App::App(const string &configFilePath) : configuration(configFilePath)
{
    targetFramerate = stof(configuration["App.targetFramerate"]);
    zBufferSize     = stoi(configuration["App.zBufferSize"]);
    finished        = false;
}

App::~App() 
{

}

void App::Run()
{
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
/*
    ARUint8 *dataPtr = arVideoGetImage();

    argDrawMode2D();
    argDispImage(dataPtr, 0, 0);
*/
}

void App::BeginPlay(int argc, char *argv[]) 
{
    glutInit(&argc, argv);

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

    char *videoInput = const_cast<char *>(configuration["camera"].c_str());

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
    
}