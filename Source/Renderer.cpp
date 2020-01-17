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
#include "MarkerMath.h"

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

void Renderer::DrawWall(const Transform &wallBegin, const Transform &wallEnd)
{
    #ifdef DEBUG
        cout << "Drawing a wall between:" << endl;
        cout << "\t[" << wallBegin[12] << ", " << wallBegin[13] << ", " << wallBegin[14] << "]" << endl;
        cout << "\t[" << wallEnd[12] << ", " << wallEnd[13] << ", " << wallEnd[14] << "]" << endl; 
    #endif // DEBUG

    const double wallLen = MarkerMath::Distance(wallBegin, wallEnd) / 80.0;

    BufferTransform (wallBegin          );

    glEnable        (GL_DEPTH_TEST      );
    glPushMatrix    (                   );
    glScaled        (wallLen, 1.0, 1.0  );
    glutWireCube    (80.f               );
    glPopMatrix     (                   );
    glDisable       (GL_DEPTH_TEST      );
}

void Renderer::DrawWholeCircle(const Vector &screenPosition)
{

}

void Renderer::DrawEmptyCircle(const Vector &screenPosition)
{

}