#include <AR/gsub.h>

#include "App.h"

#include <memory>
#include <iostream>


typedef std::shared_ptr<App> GameApp;
typedef std::shared_ptr<App> CreateApp;


void fuckingCallback();


App *app;


int main (int argc, char *argv[])
{

    app = new App();
    app->Setup(argc, argv);
    argMainLoop(nullptr, nullptr, fuckingCallback);

    return 0;
}


void fuckingCallback() { app->Run(); }
