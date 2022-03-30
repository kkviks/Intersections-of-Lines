#pragma once

#include "../AVLTree/tree.hpp"
#include "../geometry/segment.hpp"
/// <summary>
/// Implementation of the Status data structure using a balanced binary search tree (AVL).
/// </summary>
class Status : public AVLTree<Segment> {
private:

	/// <summary>
	/// Function to find the left neighbour line segment of a point.
	/// </summary>
	/// <param name="root">The root node of the Status.</param>
	/// <param name="p">The point.</param>
	/// <param name="s">The line segment object whose value will be changed to the answer.</param>
	void findLeftNeighbour(AVLNode<Segment>* root, Point& p, Segment& s) {

		if (root == nullptr)
			return;
		double x = (p.y - root->val.intercept) / root->val.slope;
		if (p.x > x) {
			s = root->val;
			findLeftNeighbour(root->right, p, s);
		}
		else {
			findLeftNeighbour(root->left, p, s);
		}
	}

	/// <summary>
	/// Function to find the right neighbour line segment of a point.
	/// </summary>
	/// <param name="root">The root node of the Status.</param>
	/// <param name="p">The point.</param>
	/// <param name="s">The line segment object whose value will be changed to the answer.</param>
	void findRightNeighbour(AVLNode<Segment>* root, Point& p, Segment& s) {

		if (root == nullptr)
			return;
		double x = (p.y - root->val.intercept) / root->val.slope;
		if (p.x < x) {
			s = root->val;
			findRightNeighbour(root->left, p, s);
		}
		else {
			findRightNeighbour(root->right, p, s);
		}
	}

	/// <summary>
	/// Function to find the left neighbour segment of a line segment.
	/// </summary>
	/// <param name="root">The root node of the Status.</param>
	/// <param name="given">The segment.</param>
	/// <param name="ans">The line segment object whose value will be changed to the answer.</param>
	void findLeftNeighbourSegment(AVLNode<Segment>* root, Segment& given, Segment& ans) {

		if (root == nullptr)
			return;

		findLeftNeighbourSegment(root->left, given, ans);

		Segment temp = root->val;
		double x_t = (Segment::k - temp.intercept) / temp.slope;
		double x_g = (Segment::k - given.intercept) / given.slope;

		if (x_t < x_g)
			ans = temp;

		findLeftNeighbourSegment(root->right, given, ans);
	}

	/// <summary>
	/// Function to find the left neighbour segment of a line segment.
	/// </summary>
	/// <param name="root">The root node of the Status.</param>
	/// <param name="given">The segment.</param>
	/// <param name="ans">The line segment object whose value will be changed to the answer.</param>
	void findRightNeighbourSegment(AVLNode<Segment>* root, Segment& given, Segment& ans) {

		if (root == nullptr)
			return;

		findRightNeighbourSegment(root->right, given, ans);

		Segment temp = root->val;
		double x_t = (Segment::k - temp.intercept) / temp.slope;
		double x_g = (Segment::k - given.intercept) / given.slope;

		if (x_t > x_g)
			ans = temp;

		findRightNeighbourSegment(root->left, given, ans);
	}

public:

	/// <summary>
	/// Helper function to find the left neighbour line segment of a point.
	/// </summary>
	/// <param name="p">The point.</param>
	/// <returns>The left neighbour line segment.</returns>
	Segment leftNeighbourOfPoint(Point& p) {
		Segment s;
		findLeftNeighbour(getRoot(), p, s);
		return s;
	}

	/// <summary>
	/// Helper function to find the right neighbour line segment of a point.
	/// </summary>
	/// <param name="p">The point.</param>
	/// <returns>The right neighbour line segment.</returns>
	Segment rightNeighbourOfPoint(Point& p) {
		Segment s;
		findRightNeighbour(getRoot(), p, s);
		return s;
	}

	/// <summary>
	/// Helper function to find the left neighbour line segment of a line segment.
	/// </summary>
	/// <param name="s">The line segment.</param>
	/// <returns>The left neighbour line segment.</returns>
	Segment leftNeighbourOfSegment(Segment& s) {
		Segment ans;
		findLeftNeighbourSegment(getRoot(), s, ans);
		return ans;
	}

	/// <summary>
	/// Helper function to find the right neighbour line segment of a line segment.
	/// </summary>
	/// <param name="s">The line segment.</param>
	/// <returns>The right neighbour line segment.</returns>
	Segment rightNeighbourOfSegment(Segment& s) {
		Segment ans;
		findRightNeighbourSegment(getRoot(), s, ans);
		return ans;
	}

	/// <summary>
	/// Function to find the leftmost line segment in the Status.
	/// </summary>
	/// <returns>The leftmost line segment in the Status.</returns>
	Segment leftMostSegment() {
		auto temp = getRoot();
		while (temp->left) {
			temp = temp->left;
		}

		return temp->val;
	}

	/// <summary>
	/// Funcion to find the rightmost line segment in the Status.
	/// </summary>
	/// <returns>The rightmost line segment in the Status.</returns>
	Segment rightMostSegment() {
		auto temp = getRoot();
		while (temp->right) {
			temp = temp->right;
		}

		return temp->val;
	}
};