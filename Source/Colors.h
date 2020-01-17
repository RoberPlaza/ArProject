/**
 * @file Colors.h
 * @author Roberto Plaza Romero (Roberto.Plaza@alu.uclm.es)
 * @brief Describes a few basic colors
 * @version 1.0
 * @date 2020-01-17
 * 
 * @copyright Copyright (c) 2020 GPL v3.0
 * 
 */


#ifndef COLOR_SAMPLES__
#define COLOR_SAMPLES__


#include "Common.h"


typedef struct Colors
{

    /**
     * @brief Color red, {255, 0, 0}
     * 
     */
    static Color red;

    /**
     * @brief Color yellow, {255, 255, 0}
     * 
     */
    static Color yellow;

    /**
     * @brief Color green, {0, 255, 0}
     * 
     */
    static Color green;

    /**
     * @brief Color cyan, {0, 255, 255}
     * 
     */
    static Color cyan;

    /**
     * @brief Color blue, {0, 0, 255}
     * 
     */
    static Color blue;

    /**
     * @brief Color magenta, {255, 0, 255}
     * 
     */
    static Color magenta;
    
    /**
     * @brief Color white, {255, 255, 255}
     * 
     */
    static Color white; 

} Colors ;


#endif // !COLOR_SAMPLES__