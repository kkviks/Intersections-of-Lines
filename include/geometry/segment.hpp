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
    Point p1;
    /// <summary>
    /// 2nd end of the line segment.
    /// </summary>
    Point p2;
    /// <summary>
    /// Slope of the line segment.
    /// </summary>
    double slope;
    /// <summary>
    /// Intercept of the line segment.
    /// </summary>
    double intercept;
    /// <summary>
    /// Location of the sweep line to sort the line segments in the Status data structure.
    /// </summary>
    static inline double k = INT_MAX;

    /// <summary>
    /// Default constructor to initialize the line segment to infinity
    /// </summary>
    Segment() {
        p1.x = p1.y = INT_MAX;
        p2.x = p2.y = INT_MAX;
        slope = intercept = INT_MAX;
    }

    /// <summary>
    /// Constructor to initialize the line segment using 2 points in the plane.
    /// </summary>
    /// <param name="p1">1st end of the line segment.</param>
    /// <param name="p2">2nd end of the line segment.</param>
    Segment(Point p1, Point p2) {
        this->p1 = p1;
        this->p2 = p2;
        slope = (p2.y - p1.y) / (p2.x - p1.x);
        intercept = p1.y - (slope * p1.x);
    }

    /// <summary>
    /// Overloading the <= operator
    /// </summary>
    /// <param name="s2"></param>
    /// <returns></returns>
    bool operator <= (Segment& s2) {
        double x = (k - intercept) / slope;
        double x2 = (k - s2.intercept) / s2.slope;
        return (abs(x - x2) < 10e-5 || x < x2);
    }

    /// <summary>
    /// Overloading the < operator.
    /// </summary>
    /// <param name="s2"></param>
    /// <returns></returns>
    bool operator < (Segment& s2) {
        double x = (k - intercept) / slope;
        double x2 = (k - s2.intercept) / s2.slope;
        return (x < x2);
    }

    /// <summary>
    /// Overloading the >= operator.
    /// </summary>
    /// <param name="s2"></param>
    /// <returns></returns>
    bool operator >= (Segment& s2) {
        double x = (k - intercept) / slope;
        double x2 = (k - s2.intercept) / s2.slope;
        return (abs(x - x2) < 10e-5 || x > x2);
    }

    /// <summary>
    /// Overloading the > operator.
    /// </summary>
    /// <param name="s2"></param>
    /// <returns></returns>
    bool operator > (Segment& s2) {
        double x = (k - intercept) / slope;
        double x2 = (k - s2.intercept) / s2.slope;
        return (x > x2);
    }

    /// <summary>
    /// Overloading the == operator.
    /// </summary>
    /// <param name="s2"></param>
    /// <returns></returns>
    bool operator == (Segment& s2) {
        return ((p1 == s2.p1 && p2 == s2.p2) || (p1 == s2.p2 && p2 == s2.p1));
    }

    /// <summary>
    /// Overloading the != operator.
    /// </summary>
    /// <param name="s2"></param>
    /// <returns></returns>
    bool operator != (Segment& s2) {
        return !((p1 == s2.p1 && p2 == s2.p2) || (p1 == s2.p2 && p2 == s2.p1));
    }

    /// <summary>
    /// Overloading the << operator to make the structure compatible with std::cout.
    /// </summary>
    /// <param name="os"></param>
    /// <param name="s"></param>
    /// <returns></returns>
    friend std::ostream& operator<<(std::ostream& os, Segment const& s) {
        return os << '[' << s.p1 << '-' << s.p2 << ']';
    }
};