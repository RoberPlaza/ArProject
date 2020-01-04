#include "Marker.h"

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

        #ifdef DEBUG
            cout << "[ " << transform[0] << ", " << transform[4] << ", " << transform[8] << ", " << transform[12] << "]" << endl;
            cout << "[ " << transform[1] << ", " << transform[5] << ", " << transform[9] << ", " << transform[13] << "]" << endl;
            cout << "[ " << transform[2] << ", " << transform[6] << ", " << transform[10] << ", " << transform[14] << "]" << endl;
            cout << "[ " << transform[3] << ", " << transform[7] << ", " << transform[11] << ", " << transform[15] << "]" << endl;
        #endif // DEBUG

        isVisible = true;
    } else {
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
    return sqrt(
        (transform[12]  - trans[12] ) * (transform[12]  - trans[12] ) +
        (transform[13]  - trans[13] ) * (transform[13]  - trans[13] ) +
        (transform[14]  - trans[14] ) * (transform[14]  - trans[14] )
    );
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
    return (transform[0] == 1.0 || transform[0] == -1.0) 
        ? atan2(transform[8], transform[14]) * 180/M_PI
        : atan2(transform[2], transform[5])  * 180/M_PI;
}

double Marker::GetPitch() const
{
    return (transform[0] == 1.0 || transform[0] == -1.0) ? 0 : asin(1) * 180/M_PI;
}

double Marker::GetRoll() const
{
    std::array<double, 3>   vectorBuffer    = {transform[0], transform[1], transform[2]};
    const double            module          = sqrt(
        pow(vectorBuffer[0], 2) +
        pow(vectorBuffer[1], 2) +
        pow(vectorBuffer[2], 2)
    );

    return acos(transform[0]/module) * 180/M_PI;
}

const Transform &Marker::GetGlTransMat() const
{
    return transform;
}

Vector Marker::GetLocation() const 
{
    return {transform[12], transform[13], transform[14]};
}