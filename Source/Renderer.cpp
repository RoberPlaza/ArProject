/**
 * @file Renderer.cpp
 * @author Roberto Plaza Romero (Robertto.Plaza@alu.uclm.es)
 * @brief Implementation of the file Renderer.h
 * @version 1.0
 * @date 2020-01-04
 * 
 * @copyright Copyright (c) 2020 GPL v3.0
 * 
 */

#include "Renderer.h"


Renderer::Renderer()
{
    int     argc            = 1;
    char    engineName[]    = "NycaTech";
    char   *argv[1]         = {engineName};

    glutInit(&argc, argv);
}

void Renderer::DrawArrow() 
{
    glEnable        (GL_DEPTH_TEST      );
    glPushMatrix    (                   );
    glScalef        (1.0f, 0.01f, 0.01f );
    glutSolidCube   (100.f              );
    glPopMatrix     (                   );
    glDisable       (GL_DEPTH_TEST      );
}

void Renderer::DrawTeapot()
{
    glEnable        (GL_DEPTH_TEST      );
    glRotatef       (90.0, 1.0, 0.0, 0.0);
    glColor3f       (1.0f, 1.0f, 1.0f   );
    glutWireTeapot  (80.f               );
    glDisable       (GL_DEPTH_TEST      );
}

void Renderer::PrepareNextFrame()
{
    glClear         (GL_DEPTH_BUFFER_BIT);
    glDepthFunc     (GL_LEQUAL          );
    glMatrixMode    (GL_MODELVIEW       );
}

void Renderer::DrawWall(const Vector &wallBegin, const Vector &wallEnd)
{

}