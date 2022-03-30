#pragma once

#include "../AVLTree/tree.hpp"
#include "../geometry/segment.hpp"
/// <summary>
/// Implementation of the Status data structure using a balanced binary search tree (AVL).
/// </summary>
class Status : public AVLTree<Segment> {
private:

	/// <summary>
	/// Function to find the leftChild neighbour line segment of a point.
	/// </summary>
	/// <param name="root">The root node of the Status.</param>
	/// <param name="p">The point.</param>
	/// <param name="s">The line segment object whose data will be changed to the answer.</param>
	void findLeftNeighbour(Node<Segment>* root, Point& p, Segment& s) {

		if (root == nullptr)
			return;
		double x = (p.y - root->data.c) / root->data.m;
		if (p.x > x) {
			s = root->data;
			findLeftNeighbour(root->rightChild, p, s);
		}
		else {
			findLeftNeighbour(root->leftChild, p, s);
		}
	}

	/// <summary>
	/// Function to find the rightChild neighbour line segment of a point.
	/// </summary>
	/// <param name="root">The root node of the Status.</param>
	/// <param name="p">The point.</param>
	/// <param name="s">The line segment object whose data will be changed to the answer.</param>
	void findRightNeighbour(Node<Segment>* root, Point& p, Segment& s) {

		if (root == nullptr)
			return;
		double x = (p.y - root->data.c) / root->data.m;
		if (p.x < x) {
			s = root->data;
			findRightNeighbour(root->leftChild, p, s);
		}
		else {
			findRightNeighbour(root->rightChild, p, s);
		}
	}

	/// <summary>
	/// Function to find the leftChild neighbour segment of a line segment.
	/// </summary>
	/// <param name="root">The root node of the Status.</param>
	/// <param name="given">The segment.</param>
	/// <param name="ans">The line segment object whose data will be changed to the answer.</param>
	void findLeftNeighbourSegment(Node<Segment>* root, Segment& given, Segment& ans) {

		if (root == nullptr)
			return;

		findLeftNeighbourSegment(root->leftChild, given, ans);

		Segment temp = root->data;
		double x_t = (Segment::k - temp.c) / temp.m;
		double x_g = (Segment::k - given.c) / given.m;

		if (x_t < x_g)
			ans = temp;

		findLeftNeighbourSegment(root->rightChild, given, ans);
	}

	/// <summary>
	/// Function to find the leftChild neighbour segment of a line segment.
	/// </summary>
	/// <param name="root">The root node of the Status.</param>
	/// <param name="given">The segment.</param>
	/// <param name="ans">The line segment object whose data will be changed to the answer.</param>
	void findRightNeighbourSegment(Node<Segment>* root, Segment& given, Segment& ans) {

		if (root == nullptr)
			return;

		findRightNeighbourSegment(root->rightChild, given, ans);

		Segment temp = root->data;
		double x_t = (Segment::k - temp.c) / temp.m;
		double x_g = (Segment::k - given.c) / given.m;

		if (x_t > x_g)
			ans = temp;

		findRightNeighbourSegment(root->leftChild, given, ans);
	}

public:

	/// <summary>
	/// Helper function to find the leftChild neighbour line segment of a point.
	/// </summary>
	/// <param name="p">The point.</param>
	/// <returns>The leftChild neighbour line segment.</returns>
	Segment leftNeighbourOfPoint(Point& p) {
		Segment s;
		findLeftNeighbour(getRoot(), p, s);
		return s;
	}

	/// <summary>
	/// Helper function to find the rightChild neighbour line segment of a point.
	/// </summary>
	/// <param name="p">The point.</param>
	/// <returns>The rightChild neighbour line segment.</returns>
	Segment rightNeighbourOfPoint(Point& p) {
		Segment s;
		findRightNeighbour(getRoot(), p, s);
		return s;
	}

	/// <summary>
	/// Helper function to find the leftChild neighbour line segment of a line segment.
	/// </summary>
	/// <param name="s">The line segment.</param>
	/// <returns>The leftChild neighbour line segment.</returns>
	Segment leftNeighbourOfSegment(Segment& s) {
		Segment ans;
		findLeftNeighbourSegment(getRoot(), s, ans);
		return ans;
	}

	/// <summary>
	/// Helper function to find the rightChild neighbour line segment of a line segment.
	/// </summary>
	/// <param name="s">The line segment.</param>
	/// <returns>The rightChild neighbour line segment.</returns>
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
		while (temp->leftChild) {
			temp = temp->leftChild;
		}

		return temp->data;
	}

	/// <summary>
	/// Funcion to find the rightmost line segment in the Status.
	/// </summary>
	/// <returns>The rightmost line segment in the Status.</returns>
	Segment rightMostSegment() {
		auto temp = getRoot();
		while (temp->rightChild) {
			temp = temp->rightChild;
		}

		return temp->data;
	}
};