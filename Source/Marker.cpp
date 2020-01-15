/**
 * @file Marker.cpp
 * @author Roberto Plaza Romero (Roberto.Plaza@alu.uclm.es)
 * @brief Implementation of the file Marker.h
 * @version 1.0
 * @date 2020-01-04
 * 
 * @copyright Copyright (c) 2020 GPL v3.0
 * 
 */

#include "Marker.h"
#include "MarkerMath.h"

#include <AR/ar.h>
#include <AR/gsub.h>
#include <AR/param.h>

#include <cmath>
#include <stdexcept>


Marker::Marker(
    const char *pattFilePath, 
    double      pattWidth, 
    double      pattDispX,
    double      pattDispY
) 
    : id(arLoadPatt(pattFilePath))
{
    if (id < 0)
        throw std::runtime_error("Unable to open Marker file");

    size            = pattWidth;
    displacement[0] = pattDispX;
    displacement[1] = pattDispY;
    isVisible       = false;
    invisibleFrames = -1;
}

Marker::~Marker ( ) { };

void Marker::Tick(float elapsedTime)
{
    
}

void Marker::DetectYourself(ARMarkerInfo **markers, int count)  
{
    int             i;
    double          netMatrix[3][4];
    ARMarkerInfo   *markerInfo = nullptr;

    for ( i = 0; i < count ; i++) {
        if (markers[i]->id == id) {
            if (!markerInfo) {
                markerInfo = markers[i];
            } else {
                markerInfo = markerInfo->cf > markers[i]->cf ? markers[i] : markerInfo;
            }
        }
    }

    if (markerInfo != nullptr) { 
        arGetTransMat(markerInfo, displacement.data(), size, netMatrix);
        argConvGlpara(netMatrix, transform.data());

        invisibleFrames--;
        isVisible = true;
    } else {
        invisibleFrames = (invisibleFrames == -1) ? -1 : invisibleFrames + 1;
        isVisible = false;
    }
}

int Marker::GetId() const
{
    return id;
}

bool Marker::IsVisible() const 
{
    return isVisible;
}

double Marker::DistanceTo(const Transform &trans) const
{
    return MarkerMath::Distance(transform, trans);
}

double Marker::Distance(const Marker &other) const 
{
    return DistanceTo(other.transform);
}

double Marker::DistanceToCamera() const 
{
    return DistanceTo(Transform({0, 0, 0})); // Camera is placed at [0, 0, 0]
}

double Marker::GetYaw() const 
{
    return MarkerMath::GetYaw(transform);
}

double Marker::GetPitch() const
{
    return MarkerMath::GetPitch(transform);
}

double Marker::GetRoll() const
{
    return MarkerMath::GetRoll(transform);
}

const Transform &Marker::GetGlTransMat() const
{
    return transform;
}

Vector Marker::GetLocation() const 
{
    return {transform[12], transform[13], transform[14]};
}