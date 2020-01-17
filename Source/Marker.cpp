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
#include <iomanip>
#include <sstream>
#include <stdexcept>


int Marker::framesToHidden = 0;


Marker::Marker(
    const char *pattFilePath, 
    double      pattWidth, 
    double      pattDispX,
    double      pattDispY
) 
    : id(arLoadPatt(pattFilePath))
{
    if (id < 0)
    {
        throw std::runtime_error("Unable to open Marker file");
    }

    size            = pattWidth;
    displacement[0] = pattDispX;
    displacement[1] = pattDispY;
    isVisible       = false;
    invisibleFrames = -1;
}

Marker::~Marker ( ) 
{ 

};

void Marker::ExtractData(ARMarkerInfo *info)
{
    double netMatrix[3][4];

    if (info) 
    {
        arGetTransMat(info, displacement.data(), size, netMatrix);
        argConvGlpara(netMatrix, transform.data());

        invisibleFrames = 0;
        isVisible       = true;
    } 
    else 
    {
        transform       = Transform();
        invisibleFrames = (invisibleFrames == -1) ? -1 : invisibleFrames + 1;
        isVisible       = false;
    }
}

void Marker::DetectYourself(ARMarkerInfo **markers, int count)  
{
    int             i;
    ARMarkerInfo   *markerInfo = nullptr;

    for ( i = 0; i < count ; i++) 
    {
        if (markers[i]->id == id) 
        {
            if (!markerInfo)  
            {
                markerInfo = markers[i];
            } 
            else 
            {  
                markerInfo = markerInfo->cf < markers[i]->cf ? markers[i] : markerInfo;
            }
        }
    }

    ExtractData(markerInfo);
}

string Marker::GetGlTransMatStr() const 
{

    stringstream ss;

    ss << "[\n" << std::fixed << std::setprecision(2);

    ss << "\t" << transform[0] << ",\t" << transform[4] << ",\t" << transform[8] << ",\t" << transform[12] << endl;
    ss << "\t" << transform[1] << ",\t" << transform[5] << ",\t" << transform[9] << ",\t" << transform[13] << endl;
    ss << "\t" << transform[2] << ",\t" << transform[6] << ",\t" << transform[10] << ",\t" << transform[14] << endl;
    ss << "\t" << transform[3] << ",\t" << transform[7] << ",\t" << transform[11] << ",\t" << transform[15] << endl;
    
    ss << "]";
    
    return ss.str();
}

int Marker::GetId() const
{
    return id;
}

bool Marker::IsVisible() const 
{
    return isVisible;
}

bool Marker::HasBeenHidden() const
{
    return (invisibleFrames != -1) && (invisibleFrames > framesToHidden);
}

double Marker::GetSize() const
{
    return size;
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