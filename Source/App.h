#ifndef RVYA_APP__
#define RVYA_APP__


#include <string>
#include <chrono>
#include <thread>
#include <vector>

#include "Pattern.h"
#include "ConfigFile.h"


/**
 * \brief Transforms a target framerate frequence to period in milliseconds
 * 
 * The class App has a member variable that stores the target framerate 
 * of the application, in order to create a timepoint that waits until the 
 * next frame this function is needed.
 * 
 * \param framerate The target framerate in frames per second.
 * \return Integer number of milliseconds to wait untill next frame.
 **/
constexpr int64_t FramerateToFrametime (float framerate)
    { return (1.f/framerate) * 1000 - 1; }

using namespace std;
using namespace chrono;
using namespace this_thread;

using Clock = system_clock;

/**
 * @brief Class to encapsulate the main workflow of the application.
 * 
 * The App class is used as a wrapper to control the frametimes, store 
 * global variables and define workflow functions.
 * 
 * \param configFilePath is the path of the .cfg or .ini file that 
 * specifies the configuration of the class.
 * 
 */
class App
{
public:
    
    App (const string &configFilePath = "./Config/Game.cfg");

    ~App ();

    App (App &&) = default; 

    App (const App &) = default;

    //App &&operator= (App &&) = default;

    App &operator= (const App &) = default;

    void Run ();

    virtual void Tick (float elapsedTime);

    virtual void BeginPlay (int argc, char *argv[]);

protected:

    ConfigFile configuration;

    vector<Pattern> usedPatterns;

    bool finished;

private:

    Clock::time_point beginTime;

    uint16_t zBufferSize;

    float targetFramerate;

    int cameraSizeX;

    int cameraSizeY;

private:

    void SetupVideoCapture();

    void CreatePatterns();

    void Cleanup();

};


#endif // !RVYA_APP__
