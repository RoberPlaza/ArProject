#include "App.h"
#include "ConfigFile.h"

#include <chrono>
#include <iostream>


App::App(const string &configFilePath)
{
    ConfigFile configFile(configFilePath);

    targetFramerate = stof(configFile["App.targetFramerate"]);
    zBufferSize     = stoi(configFile["App.zBufferSize"]);

    loopFlag        = LoopFlag::Continue;
}

App::~App() 
{

}

int App::Run(int argc, char *argv[])
{
    int returnCode = 0;

    if ((returnCode = BeginPlay()) == 0) {
        while (loopFlag == LoopFlag::Continue) {
            const Clock::time_point nextFrame = Clock::now() + milliseconds(FramerateToFrametime(targetFramerate));
            const float elapsedTime = duration_cast<microseconds>(Clock::now() - beginTime).count() / 1000000.0f; 
            
            cout << "elapsedTime is: " << elapsedTime << endl;
            returnCode = Tick(elapsedTime);

            sleep_until(nextFrame);
        }
    }

    Cleanup();

    return returnCode;
}

int App::Tick(float Delta)
{
    cout << Delta << endl;
    return Delta > 5000.0f;
}

int App::BeginPlay() 
{
    beginTime = Clock::now();

    return 0;
}

void App::Cleanup() 
{

}
