#pragma once

#include <iostream>
#include <vector>
#include <float.h>
#include <cmath>

//// <summary>
/// Class modeling point of coordinate geometry
/// </summary>
struct Point {
public:
    /// <summary>
    /// X co-ordinate of the point.
    /// </summary>
    float x;
    /// <summary>
    /// Y co-ordinate of the point.
    /// </summary>
    float y;

    /// <summary>
    /// Delta data for float comparison
    /// </summary>
    static inline float eps = 10e-5;

    /// <summary>
    /// Default constructor to initialize the point to infinity.
    /// </summary>
    Point() {
        x = y = FLT_MAX;
    }

    /// <summary>
    /// Constructor to initialize the point with x and y co-ordinate values.
    /// </summary>
    /// <param name="x">X co-ordinate of the point.</param>
    /// <param name="y">Y co-ordinate of the point.</param>
    Point(float x, float y) {
        this->x = x;
        this->y = y;
    }

    /// <summary>
    /// Overloading the <= operator.
    /// </summary>
    /// <param name="p_2"></param>
    /// <returns></returns>
    bool operator <= (Point const& p2);

    /// <summary>
    /// Overloading the >= operator.
    /// </summary>
    /// <param name="p_2"></param>
    /// <returns></returns>
    bool operator >= (Point const& p2);

    /// <summary>
    /// Overloading the < operator.
    /// </summary>
    /// <param name="p_2"></param>
    /// <returns></returns>
    bool operator < (Point const& p2);

    /// <summary>
    /// Overloading the > operator.
    /// </summary>
    /// <param name="p_2"></param>
    /// <returns></returns>
    bool operator > (Point const& p2);

    /// <summary>
    /// Overloading the == operator.
    /// </summary>
    /// <param name="p_2"></param>
    /// <returns></returns>
    bool operator == (Point const& p2);

    /// <summary>
    /// Overloading the != operator.
    /// </summary>
    /// <param name="p_2"></param>
    /// <returns></returns>
    bool operator != (Point const& p2);

    /// <summary>
    /// Overloading the << operator to make the structure compatible with std::cout.
    /// </summary>
    /// <param name="os"></param>
    /// <param name="p"></param>
    /// <returns></returns>
    friend std::ostream& operator<<(std::ostream& os, Point const& p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

bool Point:: operator <= (Point const& p2) {
    if (abs(y - p2.y) < eps) {

        if (abs(x - p2.x) < eps)
            return true;
        else
            return x < p2.x;
    }
    else
        return y > p2.y;
}

bool Point:: operator >= (Point const& p2) {
    if (abs(y - p2.y) < eps) {

        if (abs(x - p2.x) < eps)
            return true;
        else
            return x > p2.x;
    }
    else
        return y < p2.y;
}

bool Point:: operator < (Point const& p2) {
    if (abs(y - p2.y) < eps) {
        return x < p2.x;
    }
    else
        return y > p2.y;
}

bool Point::operator > (Point const& p2) {
    if (abs(y - p2.y) < eps) {
        return x > p2.x;
    }
    else
        return y < p2.y;
}

bool Point::operator == (Point const& p2) {
    return (abs(x - p2.x) < eps && abs(y - p2.y) < eps);
}

bool Point:: operator != (Point const& p2) {
    return !(abs(x - p2.x) < eps && abs(y - p2.y) < eps);
}


