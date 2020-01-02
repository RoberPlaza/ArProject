#include <GL/glut.h>    
#include <AR/gsub.h>    
#include <AR/video.h>   
#include <AR/param.h>   
#include <AR/ar.h>

#include "App.h"

int main (int argc, char *argv[])
{
    App app;
    return app.Run(argc, argv);
}