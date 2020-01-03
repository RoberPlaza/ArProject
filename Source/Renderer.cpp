#include "Renderer.h"

#include <vector>

using namespace std;


Renderer::Renderer()
{
    int     argc            = 1;
    char    engineName[]    = "NycaTech";
    char   *argv[1]         = {engineName};

    glutInit(&argc, argv);
}

void Renderer::DrawArrow() 
{
    glPushMatrix    (                   );
    glScalef        (1.0f, 0.01f, 0.01f );
    glutSolidCube   (100.f              );
    glPopMatrix     (                   );
}

void Renderer::DrawTeapot()
{
    glEnable        (GL_DEPTH_TEST      );
    glTranslatef    (0.0f, 0.0f, 50.0f  );
    glRotatef       (90.0, 1.0, 0.0, 0.0);
    glColor3f       (1.0f, 1.0f, 1.0f   );
    glutWireTeapot  (100.f              );
    glDisable       (GL_DEPTH_TEST      );
}

void Renderer::PrepareNextFrame()
{
    glClear         (GL_DEPTH_BUFFER_BIT);
    glDepthFunc     (GL_LEQUAL          );
    glMatrixMode    (GL_MODELVIEW       );
}