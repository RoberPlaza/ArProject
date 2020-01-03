#ifndef RVYA_RENDERER__
#define RVYA_RENDERER__


#include <GL/glut.h>


/**
 * @brief 
 * 
 */
enum class Figure 
{
    Arrow,
    Tower,
    Wall,
    Shield,
    MAX
};


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
    
};


#endif // !RVYA_RENDERER__