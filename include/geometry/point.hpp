#pragma once

#include <iostream>
#include <vector>
#include <float.h>
#include <cmath>

//// <summary>
/// Defines the structure of a point in a plane.
/// </summary>
struct Point {

    /// <summary>
    /// X co-ordinate of the point.
    /// </summary>
    double x;
    /// <summary>
    /// Y co-ordinate of the point.
    /// </summary>
    double y;

    /// <summary>
    /// Default constructor to initialize the point to infinity.
    /// </summary>
    Point() {
        x = y = INT_MAX;
    }

    /// <summary>
    /// Constructor to initialize the point with x and y co-ordinate values.
    /// </summary>
    /// <param name="x">X co-ordinate of the point.</param>
    /// <param name="y">Y co-ordinate of the point.</param>
    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }

    /// <summary>
    /// Overloading the <= operator.
    /// </summary>
    /// <param name="p2"></param>
    /// <returns></returns>
    bool operator <= (Point const& p2) {
        if (abs(y - p2.y) < 10e-5) {

            if (abs(x - p2.x) < 10e-5)
                return true;
            else
                return x < p2.x;
        }
        else
            return y > p2.y;
    }

    /// <summary>
    /// Overloading the >= operator.
    /// </summary>
    /// <param name="p2"></param>
    /// <returns></returns>
    bool operator >= (Point const& p2) {
        if (abs(y - p2.y) < 10e-5) {

            if (abs(x - p2.x) < 10e-5)
                return true;
            else
                return x > p2.x;
        }
        else
            return y < p2.y;
    }

    /// <summary>
    /// Overloading the < operator.
    /// </summary>
    /// <param name="p2"></param>
    /// <returns></returns>
    bool operator < (Point const& p2) {
        if (abs(y - p2.y) < 10e-5) {
            return x < p2.x;
        }
        else
            return y > p2.y;
    }

    /// <summary>
    /// Overloading the > operator.
    /// </summary>
    /// <param name="p2"></param>
    /// <returns></returns>
    bool operator > (Point const& p2) {
        if (abs(y - p2.y) < 10e-5) {
            return x > p2.x;
        }
        else
            return y < p2.y;
    }

    /// <summary>
    /// Overloading the == operator.
    /// </summary>
    /// <param name="p2"></param>
    /// <returns></returns>
    bool operator == (Point const& p2) {
        return (abs(x - p2.x) < 10e-5 && abs(y - p2.y) < 10e-5);
    }

    /// <summary>
    /// Overloading the != operator.
    /// </summary>
    /// <param name="p2"></param>
    /// <returns></returns>
    bool operator != (Point const& p2) {
        return !(abs(x - p2.x) < 10e-5 && abs(y - p2.y) < 10e-5);
    }

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