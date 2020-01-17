/**
 * @file MarkerMath.h
 * @author Roberto Plaza Romero (Roberto.Plaza@alu.uclm.es)
 * @brief Defines a struct with the operations related to marker tansforms.
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020 GPL v3.0
 * 
 */

#ifndef MARKER_MATH__
#define MARKER_MATH__


#include "Common.h"


/**
 * @brief Static struct that stores the math related to the transform 
 * of the markers.
 * 
 * @warning This class should not be instantiated, it will generate a 
 * segmentation fault since the constructor doesn't exist.
 * 
 */
typedef struct MarkerMath
{
    /**
     * @brief Construct a new Marker Math object
     * 
     * As you may see there is no constructor for this type.
     * 
     */
    MarkerMath() = delete;

    /**
     * @brief Calculates the euclidean distance between two transforms.
     * 
     * @param fist First of the transforms
     * @param second Second of the transforms.
     * @return double With the distance in milimeters between the markers.
     */
    static double Distance(const Transform &first, const Transform &second);

    /**
     * @brief Calculates the euclidean distance between vectors.
     * 
     * @param fist First of the vectors
     * @param second Second of the vectors.
     * @return double With the distance between the vectors.
     */
    static double Distance(const Vector &first, const Vector &second);

    /**
     * @brief Calculates the dot product between two vectors.
     * 
     * @param first vector
     * @param second vector
     * @return double with the result
     */
    static double DotProduct(const Vector &first, const Vector &second);

    /**
     * @brief Calculates the rotation in the Z axis between 2 vectors
     * 
     * @param first vector
     * @param second vector
     * @return double with the angle in degrees.
     */
    static double GetRoll(const Vector &first, const Vector &second);

    /**
     * @brief Get the rotation in the X axis of a marker. 
     * 
     * @warning Result may not be accurate.
     * 
     * @param markerTransform Transform matrix of the marker.
     * @return double With the rotation in degrees.
     */
    static double GetYaw(const Transform &markerTransform);

    /**
     * @brief Get the rotation in the Y axis of a marker.
     * 
     * @warning Result may not be accurate.
     * 
     * @param markerTransform Transform matrix of the marker.
     * @return double With the rotation in degrees.
     */
    static double GetPitch(const Transform &markerTransform);

    /**
     * @brief Get the rotation in the Z axis of a marker. 
     * 
     * @param markerTransform Transform matrix of the marker.
     * @return double With the rotation in degrees.
     */
    static double GetRoll(const Transform &markerTransform);

    /**
     * @brief Calculates the cross product of two vectors.
     * 
     * @param first First vector.
     * @param second Second vector.
     * @return Vector with the result.
     */
    static Vector CrossProduct(const Vector &first, const Vector &second);

    /**
     * @brief Calculates the cross product of two vectors and normalizes it.
     * 
     * @param first First vector.
     * @param second Second vector.
     * @return Vector with the result.
     */
    static Vector NormalizeCrossProduct(const Vector &first, const Vector &second);

} MarkerMath;


#endif // !MARKER_MATH__
