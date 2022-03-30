#pragma once

#include <iostream>
#include <vector>
#include <float.h>
#include <cmath>

#include "point.hpp"
#include "segment.hpp"

const int eps = 1e-5;

/// <summary>
/// Function to see if 3 points lie on the given line segment.
/// </summary>
/// <param name="p">1st point.</param>
/// <param name="q">2nd point.</param>
/// <param name="r">3rd point.</param>
/// <returns>True, if they all lie on the same segment; False if they don't.</returns>
bool onSegment(Point p, Point q, Point r)
{
	if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
		q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
		return true;

	return false;
}

/// <summary>
/// Function to find the orientation of the points in the plane.
/// </summary>
/// <param name="p">1st point.</param>
/// <param name="q">2nd point.</param>
/// <param name="r">3rd point.</param>
/// <returns>0, if the points are collinear; 1 if they are clockwise aligned; 2 if they are anti-clockwise aligned.</returns>
int orientation(Point p, Point q, Point r)
{
	// See https://www.geeksforgeeks.org/orientation-3-ordered-points/
	// for details of below formula.
	float val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (std::abs(val) < eps) return 0;  // collinear

	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

/// <summary>
/// Function to find if 2 line segments intersect.
/// </summary>
/// <param name="p_1">1st endpoint of the 1st line segment.</param>
/// <param name="q1">2nd endpoint of the 1st line segment.</param>
/// <param name="p_2">1st endpoint of the 2nd line segment.</param>
/// <param name="q2">2nd endpoint of the 2nd line segment.</param>
/// <returns>True, if the line segments intersect; False if they don't.</returns>
bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
	// Find the four orientations needed for general and
	// special cases
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p_1, q1 and p_2 are collinear and p_2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p_1, q1 and q2 are collinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p_2, q2 and p_1 are collinear and p_1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p_2, q2 and q1 are collinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases
}

/// <summary>
/// Calculates the point of intersection of 2 lines.
/// </summary>
/// <param name="A">1st point in the 1st line.</param>
/// <param name="B">2nd point in the 1st line.</param>
/// <param name="C">1st point in the 2nd line.</param>
/// <param name="D">2nd point in the 2nd line.</param>
/// <returns>The point of intersection of the 2 lines.</returns>
Point intersection(Point A, Point B, Point C, Point D)
{
	// Line AB represented as a1x + b1y = c1
	float a1 = B.y - A.y;
	float b1 = A.x - B.x;
	float c1 = a1 * (A.x) + b1 * (A.y);

	// Line CD represented as a2x + b2y = c2
	float a2 = D.y - C.y;
	float b2 = C.x - D.x;
	float c2 = a2 * (C.x) + b2 * (C.y);

	float determinant = a1 * b2 - a2 * b1; // determinant for a 2 dimensional matrix by Cramer's rule is calculated here

	if (determinant == 0)	//If deteminant is 0 the lines are parallel and hence the point of intersection is set as inf, inf
	{
		Point p1(FLT_MAX, FLT_MAX);
		return p1;
	}
	else					// if the lines aren't parallel, the x and y cordinates are calculated by the following equation
	{
		float x = (b2 * c1 - b1 * c2) / determinant;
		float y = (a1 * c2 - a2 * c1) / determinant;
		Point p1(x, y);
		return p1;
	}
}

