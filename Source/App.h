#ifndef RVYA_APP__
#define RVYA_APP__


#include <string>
#include <chrono>
#include <thread>


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
 * \enum LoopFlag is an enum used to decide what to do in the next iteration
 * of the program.
 **/
enum class LoopFlag : uint8_t 
{ 
    Exit        = 0,
    Continue    = 1,
    Pause       = 2,
    MAX         = 3
};


class App
{
public:
    
    App (const string &configFilePath = "./Config/Game.cfg");

    ~App ();

    App (App &&) = delete;

    App (const App &) = delete;

    App &&operator= (App &&) = delete;

    App &operator= (const App &) = delete;

    int Run (int argc, char *argv[]);

    virtual int Tick(float Delta);

    virtual int BeginPlay();

protected:

    LoopFlag loopFlag;

private:

    Clock::time_point beginTime;

    uint16_t zBufferSize;

    float targetFramerate;

    void Cleanup();

};


#endif // !RVYA_APP__
