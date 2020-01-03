#include <AR/gsub.h>

#include "App.h"

#include <memory>
#include <iostream>


typedef std::shared_ptr<App> GameApp;


void fuckingCallback();


GameApp app;


int main (int argc, char *argv[])
{

    app = make_shared<App>(argc > 1 ? argv[1] : "Config/Game.cfg");
    app->Setup();
    
    argMainLoop(nullptr, nullptr, fuckingCallback);

    return 0;
}


void fuckingCallback () { app->Run(); }
