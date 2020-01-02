#include <AR/gsub.h>

#include "App.h"

#include <memory>
#include <iostream>
#include <functional>


using namespace std;


typedef unique_ptr<App> GameApp;
typedef unique_ptr<App> CreateApp;


GameApp app;


void fuckCallbacks();


int main (int argc, char *argv[])
{
    app = make_unique<App>();
    app->BeginPlay(argc, argv);

    argMainLoop(nullptr, nullptr, fuckCallbacks);

    return 0;
}


void fuckCallbacks()
{
    app->Run();
}
