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
struct LUData {
    /// <summary>
    /// The point for which we will be storing the line segments having it as an lower / upper endpoint.
    /// </summary>
    Point key;
    /// <summary>
    /// Vector to store all the line segments.
    /// </summary>
    std::vector<Segment> list;

    LUData() {}

    /// <summary>
    /// Constructor to initialize the LUData structure.
    /// </summary>
    /// <param name="key">The point for which this structure is storing the line segments.</param>
    LUData(Point key) {
        this->key = key;
    }

    /// <summary>
    /// Overloading the < operator.
    /// </summary>
    /// <param name="t2"></param>
    /// <returns></returns>
    bool operator < (LUData const& t2) {
        return key < t2.key;
    }

    /// <summary>
    /// Overloading the <= operator.
    /// </summary>
    /// <param name="t2"></param>
    /// <returns></returns>
    bool operator <= (LUData const& t2) {
        return key <= t2.key;
    }

    /// <summary>
    /// Overloading the > operator.
    /// </summary>
    /// <param name="t2"></param>
    /// <returns></returns>
    bool operator > (LUData const& t2) {
        return key > t2.key;
    }

    /// <summary>
    /// Overloading the >= operator.
    /// </summary>
    /// <param name="t2"></param>
    /// <returns></returns>
    bool operator >= (LUData const& t2) {
        return key >= t2.key;
    }

    /// <summary>
    /// Overloading the == operator.
    /// </summary>
    /// <param name="t2"></param>
    /// <returns></returns>
    bool operator == (LUData const& t2) {
        return key == t2.key;
    }

    /// <summary>
    /// Overloading the != operator.
    /// </summary>
    /// <param name="t2"></param>
    /// <returns></returns>
    bool operator != (LUData const& t2) {
        return key != t2.key;
    }

    /// <summary>
    /// Overloading the << operator to make the structure compatible with std::cout.
    /// </summary>
    /// <param name="os"></param>
    /// <param name="t"></param>
    /// <returns></returns>
    friend std::ostream& operator<<(std::ostream& os, LUData const& t) {
        os << t.key;
        os << '[';
        for (unsigned int i = 0; i < t.list.size(); i++) {
            os << t.list[i];
            if (i != t.list.size() - 1)
                os << ", ";
        }
        os << "]\n";
        return os;
    }
};
