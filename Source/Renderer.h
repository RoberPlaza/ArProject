/**
 * @file Renderer.h
 * @author Roberto Plaza Romero (Roberto.Plaza@alu.uclm.es)
 * @brief This file specifies a Renderer class, used to draw things.
 * @version 1.0
 * @date 2020-01-04
 * 
 * @copyright Copyright (c) 2020 GLP v3.0
 * 
 */
#ifndef RVYA_RENDERER__
#define RVYA_RENDERER__


#include <GL/glut.h>

#include "Common.h"


/**
 * @brief Class to render different shapes.
 * 
 * The models to render will not be based on any standard.
 * Every model will be drawn used the glut models.
 * 
 */
class Renderer
{
public:

    /**
     * @brief Construct a new Renderer object
     * 
     */
    Renderer();

    /**
     * @brief Clears the opengl buffer and enables depth buffer.
     * 
     */
    void PrepareNextFrame();

    /**
     * @brief Draws an Arrow.
     * 
     * @note To change the transform push them to the OpenGL 
     * stack before calling the function.
     * 
     */
    void DrawArrow();

    /**
     * @brief Draws a Teapot.
     * 
     * @note only to be used as sparring.
     * 
     */
    void DrawTeapot();


    /**
     * @brief Draws a wall that spawns to a point in space.
     * 
     * @param wallBegin Is the position in space where the wall begins.
     * @param wallEnd Position were the wall ends.
     */
    void DrawWall(const Transform &wallBegin, const Transform &wallEnd);

private:

    /**
     * @brief Function to be called before buffering vertices.
     * 
     */
    void PreBuffering();

    /**
     * @brief Function to be called after buffering vertices.
     * 
     */
    void PostBuffering();
    
};


#endif // !RVYA_RENDERER__