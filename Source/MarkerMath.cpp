#include "MarkerMath.h"

#include <cmath>


double MarkerMath::Distance(const Transform &first, const Transform &second)
{
    const Vector firstPosition  = {first[12],   first[13],  first[14]};
    const Vector secondPosition = {second[12],  second[13], second[14]};

    return Distance(firstPosition, secondPosition);
}

double MarkerMath::Distance(const Vector &first, const Vector &second)
{
    return sqrt(
        (first[0] - second[0]) * (first[0] - second[0]) +
        (first[1] - second[1]) * (first[1] - second[1]) +
        (first[2] - second[2]) * (first[2] - second[2])
    );
}

double MarkerMath::DotProduct(const Vector &first, const Vector &second)
{
    static int  i       = 0;
    double      result  = 0.0;

    for (i = 0; i < 3; i++) 
    {
        result += first[i] * second[i];
    }

    return result;
}

double MarkerMath::GetRoll(const Vector &first, const Vector &second)
{
    const Vector Buffer = 
        {first[0] - second[0], first[1] - second[1], first[2] - second[2]};

    return (atan2(Buffer[1], Buffer[0]) * 180/M_PI) ;
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

Vector MarkerMath::CrossProduct(const Vector &first, const Vector &second)
{
    Vector result;
    
    result[0] = first[1] * second[2] - first[2] * second[1];
    result[1] = first[0] * second[2] - first[2] * second[0];
    result[2] = first[0] * second[1] - first[1] * second[0];

    return result;
}

Vector MarkerMath::NormalizeCrossProduct(const Vector &first, const Vector &second)
{
    Vector          result  = CrossProduct(first, second);
    const double    length  = Distance(first, second);

    result[0] /= length;
    result[1] /= length;
    result[2] /= length;

    return result;
}