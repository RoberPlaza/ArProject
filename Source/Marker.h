#ifndef RVYA_MARKER__
#define RVYA_MARKER__

#include <AR/ar.h>


#include <array>

typedef std::array<double[4], 3>    Transform;
typedef std::array<double, 2>       Center;


/**
 * @brief This class encapsulates the information of a Marker.
 * 
 * Easy handler for the functions of a Marker and some information 
 * regarding them. Also could be inherit in order to create a multipattern.
 * 
 */
class Marker
{
public:
    
    /**
     * @brief Construct a new Marker object
     * 
     * 
     * @param pattFilePath Path to the file of the Marker, commonly saved with a .patt extension.
     * @param pattWidth Width of the Marker in milimeters.
     * @param pattDisp Displacements of the Marker, used for the Multipattern.
     */
    Marker( const char *pattFilePath    =   "Resources/Markers/Default.patt", 
            double      pattWidth       =   120.0,
            Center      pattDisp        =   {0.0, 0.0});

    /**
     * @brief Updates the information regarding the markers.
     * 
     * Each frame the Tick function should be called with the information
     * of the camera. The information regarding the net matrix will not be 
     * up-to-date untill the new Tick.
     * 
     * @param elapsedTime Time passed since the game started
     * @param data Pointer to the data of the camera
     */
    void Tick(float elapsedTime, ARUint8 *data);

private:

    /**
     * @brief Information about the transform of the Marker.
     * 
     */
    Transform       netMatrix;

    /**
     * @brief Used for the multipatterns.
     * 
     */
    Center          displacement;

    /**
     * @brief Structure for handle aplication.
     * 
     */
    ARMarkerInfo   *markerInfo;

    /**
     * @brief Id of the marker.
     * 
     */
    int             id;

    /**
     * @brief Black/White threshold for the detection algorithm.
     * 
     */
    int             threshold;

    /**
     * @brief Width in milimeters of the Marker.
     * 
     */
    double          size;
};

#endif // !RVYA_MARKER__