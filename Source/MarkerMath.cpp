#include "MarkerMath.h"

#include <cmath>


double MarkerMath::Distance(const Transform &first, const Transform &second)
{
    return sqrt(
        (first[12]  - second[12] ) * (first[12]  - second[12] ) +
        (first[13]  - second[13] ) * (first[13]  - second[13] ) +
        (first[14]  - second[14] ) * (first[14]  - second[14] )
    );
}

double MarkerMath::GetYaw(const Transform &markerTransform)
{
    return (markerTransform[0] == 1.0 || markerTransform[0] == -1.0) 
        ? atan2(markerTransform[8], markerTransform[14]) * 180/M_PI
        : atan2(markerTransform[2], markerTransform[5])  * 180/M_PI;
}

double MarkerMath::GetPitch(const Transform &markerTransform)
{
    return (markerTransform[0] == 1.0 || markerTransform[0] == -1.0) ? 0 : asin(1) * 180/M_PI;
}

double MarkerMath::GetRoll(const Transform &markerTransform)
{
    const double module = sqrt(
        pow(markerTransform[0], 2) +
        pow(markerTransform[1], 2) +
        pow(markerTransform[2], 2)
    );

    return acos(markerTransform[0]/module) * 180/M_PI;
}