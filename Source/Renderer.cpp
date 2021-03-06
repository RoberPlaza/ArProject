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

#include <AR/gsub.h>

#include <cmath>


void Renderer::PrepareNextFrame()
{
    argDrawMode3D   (                   );
    argDraw3dCamera (0, 0               );
    glClear         (GL_DEPTH_BUFFER_BIT);
    glEnable        (GL_DEPTH_TEST      );
    glDepthFunc     (GL_LEQUAL          );
}

Renderer::Renderer()
{
    int     argc            = 1;
    char    engineName[]    = "NycaTech";
    char   *argv[1]         = {engineName};

    glutInit(&argc, argv);
}

void Renderer::BufferTransform(const Transform &transform)
{
    glMatrixMode    (GL_MODELVIEW       );
    glLoadMatrixd   (transform.data()   );
}

void Renderer::PostBuffering()
{
    glDisable       (GL_DEPTH_TEST      );
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
    glTranslatef    (0.0f, 0.0f, 60.0f  );
    glRotatef       (90.0, 1.0, 0.0, 0.0);
    glColor3f       (1.0f, 1.0f, 1.0f   );
    glutWireTeapot  (80.f               );
    glDisable       (GL_DEPTH_TEST      );
}

void Renderer::DrawCube(double size)
{
    glEnable        (GL_DEPTH_TEST      );
    glutSolidCube   (size               );
    glDisable       (GL_DEPTH_TEST      );
}

void Renderer::DrawWall(double angle, double length, double size)
{

    glEnable        (GL_DEPTH_TEST      );
    glPushMatrix    (                   );
    glRotated       (angle, 0, 0, 1     );
    glTranslated    (length*size/2.0 - size/2.0, 0., 0    );
    glScaled        (length, 1., 1.     );
    glutWireCube    (size               );
    glPopMatrix     (                   );
    glDisable       (GL_DEPTH_TEST      );
}

void Renderer::DrawWholeCircle()
{
    glPushMatrix    (                   );
    glutSolidSphere (8.0, 25, 25        );
    glPopMatrix     (                   );
}

void Renderer::DrawEmptyCircle()
{
    glPushMatrix    (                   );
    glutWireSphere  (8.0, 25, 25        );
    glPopMatrix     (                   );
}

void Renderer::BufferColor(const Color &color)
{
    glColor3f(color[0], color[1], color[2]);
}