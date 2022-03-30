#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

#include "./include/geometry/point.hpp"
#include "./include/geometry/segment.hpp"
#include "./include/geometry/helpers.hpp"
#include "./include/geometry/Common.hpp"

#include "./include/AVLTree/tree.hpp"

#include "./include/ds/event_queue.hpp"
#include "./include/ds/status.hpp"

using namespace std;

/// <summary>
/// File to store the output data into.
/// </summary>
ofstream outputFile("./output.txt");

/// <summary>
/// File to store the input data into.
/// </summary>
ofstream inputFile("./input.txt");

/// <summary>
/// Creating the event queue data structure.
/// </summary>
EventQueue<Point> eq;
/// <summary>
/// Creating an AVL Tree to store all the line segments that have a particular point as it's lower point.
/// </summary>
AVLTree<Common> L;
/// <summary>
/// Creating an AVL Tree to store all the line segments that have a particular point as it's upper point.
/// </summary>
AVLTree<Common> U;
/// <summary>
/// Creating an AVL Tree to store all the line segments that have a particular point containing a line segment.
/// </summary>
AVLTree<Common> C;
/// <summary>
/// Creating an AVL Tree to store all the intersection points of the line segments.
/// </summary>
AVLTree<Point> finalAns;
/// <summary>
/// Creating the Status data structure.
/// </summary>
Status T;

/// <summary>
/// Function to find a new event point from the current event point being processed.
/// </summary>
/// <param name="s1">Line segment 1.</param>
/// <param name="s2">Line segment 2.</param>
/// <param name="p">The event point being processed.</param>
void findNewEvent(Segment s1, Segment s2, Point p) {

	Point temp = intersection(s1.p_1, s1.p_2, s2.p_1, s2.p_2);

	if (!doIntersect(s1.p_1, s1.p_2, s2.p_1, s2.p_2))
		return;
	else if (temp.y < p.y || (abs(temp.y - Segment::k) < 10e-5 && temp.x > p.x)) {
		eq.insert(temp);

		Common t;
		t.commonPoint = temp;
		t.segments.push_back(s1);
		t.segments.push_back(s2);

		auto t2 = C.search(t);

		if (t2) {
			t2->data.segments.push_back(s1);
			t2->data.segments.push_back(s2);
		}
		else
			C.insert(t);
	}
}

/// <summary>
/// Function to handle an event point popped from the event queue.
/// </summary>
/// <param name="p">The event point.</param>
void handleEvent(Point& p) {

	Node<Common>* u = U.search(p);
	Node<Common>* l = L.search(p);
	Node<Common>* c = C.search(p);
	Status union_;
	union_.clear();

	if (u)
		for (Segment& s : u->data.segments)
			union_.insert(s);
	if (l)
		for (Segment& s : l->data.segments)
			union_.insert(s);
	if (c)
		for (Segment& s : c->data.segments)
			union_.insert(s);

	if (union_.getRoot())
		if (union_.getRoot()->leftChild || union_.getRoot()->rightChild) {
			if (!finalAns.search(p))
				outputFile << p.x << ' ' << p.y << '\n';
			finalAns.insert(p);
		}

	union_.clear();

	if (l)
		for (Segment& s : l->data.segments)
			union_.insert(s);
	if (c)
		for (Segment& s : c->data.segments)
			union_.insert(s);

	T.difference(union_);
	Segment::k = p.y - (2 * 10e-5);

	if (u)
		for (Segment& s : u->data.segments)
			T.insert(s);
	if (c)
		for (Segment& s : c->data.segments)
			T.insert(s);

	union_.clear();

	if (u)
		for (Segment& s : u->data.segments)
			union_.insert(s);
	if (c)
		for (Segment& s : c->data.segments)
			union_.insert(s);

	if (!union_.getRoot()) {
		Segment bLeft = T.leftNeighbourOfPoint(p);
		Segment bRight = T.rightNeighbourOfPoint(p);
		findNewEvent(bLeft, bRight, p);
	}
	else {
		Segment bLeft;
		Segment bRight;
		Segment sLeft = union_.leftMostSegment();
		Segment sRight = union_.rightMostSegment();
		bLeft = T.leftNeighbourOfSegment(sLeft);
		bRight = T.rightNeighbourOfSegment(sRight);

		findNewEvent(bLeft, sLeft, p);
		findNewEvent(bRight, sRight, p);
	}
}

int main() {

	int n;

	cout << "Enter the number of line segments: ";
	cin >> n;

	inputFile << n << '\n';

	// Input the line segments and initialize all the required data structures
	for (int i = 0; i < n; i++) {
		double x1, y1, x2, y2;
		cout << "Enter the 2 points of the line segment: ";
		cin >> x1 >> y1 >> x2 >> y2;

		inputFile << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';

		Point p1(x1, y1);
		Point p2(x2, y2);

		Segment s(p1, p2);

		Common t;

		if (p1 > p2) {
			t.commonPoint = p1;
			t.segments.push_back(s);

			Node<Common>* temp = L.search(t);

			if (temp)
				temp->data.segments.push_back(s);
			else
				L.insert(t);

			t.commonPoint = p2;

			temp = U.search(t);

			if (temp)
				temp->data.segments.push_back(s);
			else
				U.insert(t);
		}
		else {
			t.commonPoint = p2;
			t.segments.push_back(s);

			Node<Common>* temp = L.search(t);

			if (temp)
				temp->data.segments.push_back(s);
			else
				L.insert(t);

			t.commonPoint = p1;

			temp = U.search(t);

			if (temp)
				temp->data.segments.push_back(s);
			else
				U.insert(t);
		}

		eq.insert(p1);
		eq.insert(p2);
	}

	// Starting the clock to measure time
	auto start = chrono::high_resolution_clock::now();

	// Processing all the event points
	while (!eq.empty()) {
		Point p = eq.top();
		eq.pop();
		handleEvent(p);
	}

	// Stopping the clock
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

	cout << "\nThe intersection points are : ";
	finalAns.display();
	cout << "\nCalculation done in " << duration.count() << " microseconds.";

	inputFile.close();
	outputFile.close();

	//system("python plotter.py");
	return 0;
}