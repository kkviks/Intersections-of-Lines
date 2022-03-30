#pragma once

#include <iostream>
#include <vector>
#include <float.h>
#include <cmath>

#include "point.hpp"
#include "segment.hpp"

using namespace std;

//// <summary>
/// Defines a structure to store the line segments having lower / upper endpoints at a particular point.
/// </summary>
struct Common {
    /// <summary>
    /// The point for which we will be storing the line segments having it as an lower / upper endpoint.
    /// </summary>
    Point commonPoint;
    /// <summary>
    /// Vector to store all the line segments.
    /// </summary>
    vector<Segment> segments;

    Common() {}

    /// <summary>
    /// Constructor to initialize the Common structure.
    /// </summary>
    /// <param name="commonPoint">The point for which this structure is storing the line segments.</param>
    Common(Point point) {
        this->commonPoint = point;
    }

    /// <summary>
    /// Overloading the < operator.
    /// </summary>
    /// <param name="t2"></param>
    /// <returns></returns>
    bool operator < (Common const& t2);

    /// <summary>
    /// Overloading the <= operator.
    /// </summary>
    /// <param name="t2"></param>
    /// <returns></returns>
    bool operator <= (Common const& t2);

    /// <summary>
    /// Overloading the > operator.
    /// </summary>
    /// <param name="t2"></param>
    /// <returns></returns>
    bool operator > (Common const& t2);

    /// <summary>
    /// Overloading the >= operator.
    /// </summary>
    /// <param name="t2"></param>
    /// <returns></returns>
    bool operator >= (Common const& t2);

    /// <summary>
    /// Overloading the == operator.
    /// </summary>
    /// <param name="t2"></param>
    /// <returns></returns>
    bool operator == (Common const& t2);

    /// <summary>
    /// Overloading the != operator.
    /// </summary>
    /// <param name="t2"></param>
    /// <returns></returns>
    bool operator != (Common const& t2);

    /// <summary>
    /// Overloading the << operator to make the structure compatible with std::cout.
    /// </summary>
    /// <param name="os"></param>
    /// <param name="t"></param>
    /// <returns></returns>
    friend std::ostream& operator<<(std::ostream& os, Common const& t) {
        os << t.commonPoint;
        os << '[';
        for (unsigned int i = 0; i < t.segments.size(); i++) {
            os << t.segments[i];
            if (i != t.segments.size() - 1)
                os << ", ";
        }
        os << "]\n";
        return os;
    }
};


bool Common::operator < (Common const& t2) {
    return commonPoint < t2.commonPoint;
}


bool Common::operator <= (Common const& t2) {
    return commonPoint <= t2.commonPoint;
}

bool Common::operator > (Common const& t2) {
    return commonPoint > t2.commonPoint;
}

bool Common::operator >= (Common const& t2) {
    return commonPoint >= t2.commonPoint;
}

bool Common::operator == (Common const& t2) {
    return commonPoint == t2.commonPoint;
}

bool Common::operator != (Common const& t2) {
    return commonPoint != t2.commonPoint;
}

