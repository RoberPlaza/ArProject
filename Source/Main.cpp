/**
 * @file Main.cpp
 * @author Roberto Plaza Romero (Roberto.Plaza@alu.uclm.es)
 * @brief Entrypoint of the application.
 * @version 1.0
 * @date 2020-01-04
 * 
 * @copyright Copyright (c) 2020 GPL v3.0
 * 
 */
#include <AR/gsub.h>

#include "App.h"

#include <memory>


void fuckingCallback();


GameApp app;


/**
 * @brief Entrypoint of any program.
 * 
 * Since the main loop should be executed in argMainLoop I needed to code 
 * a wrapper. Intended way is to call Setup() in an App and then Run() it.
 * 
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return int = 0 if everything was OK.
 */
int main (int argc, char *argv[])
{
    app = make_shared<App>(argc > 1 ? argv[1] : "Config/Game.cfg");
    app->Setup();

    argMainLoop(nullptr, nullptr, fuckingCallback);

    return 0;
}


void fuckingCallback () 
{ 
    app->Run(); 
}
