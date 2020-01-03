#include "Marker.h"

#include <AR/ar.h>

Marker::Marker(
        const char *pattFilePath, 
        double      pattWidth, 
        Center      pattDisp
    ) 
    : displacement(pattDisp), id(arLoadPatt(pattFilePath))
{
    if (id < 0)
        throw std::runtime_error("Unable to open Marker file");

    size       = pattWidth;
}

void Marker::Tick(float elapsedTime, ARUint8 *data)
{
    arGetTransMat(markerInfo, displacement.data(), size, netMatrix.data());
}
