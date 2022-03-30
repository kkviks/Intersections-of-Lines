#pragma once

#include <iostream>
#include <vector>
#include <float.h>
#include <cmath>

#include "point.hpp"

/// <summary>
/// Defines the structure of a line segment.
/// </summary>
class Segment {
public:
    /// <summary>
    /// 1st end of the line segment.
    /// </summary>
    Point p_1;
    /// <summary>
    /// 2nd end of the line segment.
    /// </summary>
    Point p_2;
    /// <summary>
    /// Slope of the line segment.
    /// </summary>
    float m;
    /// <summary>
    /// Intercept of the line segment.
    /// </summary>
    float c;
    /// <summary>
    /// Location of the sweep line to sort the line segments in the Status data structure.
    /// </summary>
    static inline float k = FLT_MAX;
    static inline float eps = 10e-5;

    /// <summary>
    /// Default constructor to initialize the line segment to infinity
    /// </summary>
    Segment() {
        p_1.x = p_1.y = FLT_MAX;
        p_2.x = p_2.y = FLT_MAX;
        m = c = FLT_MAX;
    }

    /// <summary>
    /// Constructor to initialize the line segment using 2 points in the plane.
    /// </summary>
    /// <param name="p_1">1st end of the line segment.</param>
    /// <param name="p_2">2nd end of the line segment.</param>
    Segment(Point p1, Point p2) {
        this->p_1 = p1;
        this->p_2 = p2;
        m = (p2.y - p1.y) / (p2.x - p1.x);
        c = p1.y - (m * p1.x);
    }

    /// <summary>
    /// Overloading the <= operator
    /// </summary>
    /// <param name="s2"></param>
    /// <returns></returns>
    bool operator <= (Segment& s2);

    /// <summary>
    /// Overloading the < operator.
    /// </summary>
    /// <param name="s2"></param>
    /// <returns></returns>
    bool operator < (Segment& s2);

    /// <summary>
    /// Overloading the >= operator.
    /// </summary>
    /// <param name="s2"></param>
    /// <returns></returns>
    bool operator >= (Segment& s2);

    /// <summary>
    /// Overloading the > operator.
    /// </summary>
    /// <param name="s2"></param>
    /// <returns></returns>
    bool operator > (Segment& s2);

    /// <summary>
    /// Overloading the == operator.
    /// </summary>
    /// <param name="s2"></param>
    /// <returns></returns>
    bool operator == (Segment& s2);

    /// <summary>
    /// Overloading the != operator.
    /// </summary>
    /// <param name="s2"></param>
    /// <returns></returns>
    bool operator != (Segment& s2);

    /// <summary>
    /// Overloading the << operator to make the structure compatible with std::cout.
    /// </summary>
    /// <param name="os"></param>
    /// <param name="s"></param>
    /// <returns></returns>
    friend std::ostream& operator<<(std::ostream& os, Segment const& s) {
        return os << '[' << s.p_1 << '-' << s.p_2 << ']';
    }
};


bool Segment:: operator <= (Segment& s2) {
    float x = (k - c) / m;
    float x2 = (k - s2.c) / s2.m;
    return (abs(x - x2) < eps || x < x2);
}

bool Segment:: operator < (Segment& s2) {
    float x = (k - c) / m;
    float x2 = (k - s2.c) / s2.m;
    return (x < x2);
}


bool Segment:: operator >= (Segment& s2) {
    float x = (k - c) / m;
    float x2 = (k - s2.c) / s2.m;
    return (abs(x - x2) < eps or x > x2);
}


bool Segment:: operator > (Segment& s2) {
    float x = (k - c) / m;
    float x2 = (k - s2.c) / s2.m;
    return (x > x2);
}


bool Segment:: operator == (Segment& s2) {
    return ((p_1 == s2.p_1 && p_2 == s2.p_2) or (p_1 == s2.p_2 && p_2 == s2.p_1));
}

bool Segment:: operator != (Segment& s2) {
    return !((p_1 == s2.p_1 && p_2 == s2.p_2) or (p_1 == s2.p_2 && p_2 == s2.p_1));
}
