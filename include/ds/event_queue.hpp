#ifndef QUEUE_H
#define QUEUE_H

#include "../AVLTree/tree.hpp"

template <class T>
/// <summary>
/// Implementation of the event queue data structure using a balance binary tree (AVL).
/// </summary>
/// <typeparam name="T">A template class.</typeparam>
class EventQueue {
public:

	/// <summary>
	/// Constructor to initialize the event queue.
	/// </summary>
	EventQueue() {
		tree = new AVLTree<T>();
	}

	/// <summary>
	/// Function to insert a value into the event queue.
	/// </summary>
	/// <param name="val">The value to be inserted into the event queue.</param>
	void insert(T val) {
		tree->insert(val);
	}

	/// <summary>
	/// Function to get the highest priority element in the event queue.
	/// </summary>
	/// <returns>The highest priority element in the event queue.</returns>
	T top() {
		AVLNode<T>* temp = tree->getRoot();  // get the root of the current tree 
		while (temp->left) {    //traverse to the left node until the next pointer is not NULL
			temp = temp->left;
		}
		return temp->val;   // return the value of the leftmost element in the AVL tree
	}

	/// <summary>
	/// Function to pop the highest priority element in the event queue.
	/// </summary>
	void pop() {
		tree->remove(this->top());
	}

	/// <summary>
	/// Function to display the event queue.
	/// </summary>
	void display() {
		tree->display();
	}

	/// <summary>
	/// Function to check if the event queue is empty.
	/// </summary>
	/// <returns>True, if the queue is empty; False if otherwise.</returns>
	bool empty() {
		return tree->getRoot() == nullptr;
	}

private:
	/// <summary>
	/// Pointer to the AVL Tree which is used to implement this data structure.
	/// </summary>
	AVLTree<T>* tree;
};

#endif