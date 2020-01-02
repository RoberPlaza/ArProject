#ifndef RVYA_PATT__
#define RVYA_PATT__

#include <AR/ar.h>

#include <array>


typedef std::array<double, 12> Transform;
typedef std::pair<double, double> Displacement;

class Pattern
{
public:
    
    Pattern();

    ~Pattern();

    Pattern (Pattern &&) = delete;
    
    Pattern (const Pattern &&) = delete;

    Pattern &&operator= (Pattern &&) = delete;

    Pattern &operator=(const Pattern &) = delete;

private:

    Transform netMatrix;

    Displacement displacement;

    ARMarkerInfo *markerInfo;

    int id;

    double width;
};

#endif // !RVYA_PATT__