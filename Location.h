#ifndef LOCATION_H
#define LOCATION_H
// Define a class to represent a location in the Euclidean plane.
class Location
{
public:
    double x;
    double y;
    int rank;
// Define the equality operator for the Location class.
    bool operator==(const Location& other) const
    {
        return x == other.x && y == other.y;
    }
};
#endif