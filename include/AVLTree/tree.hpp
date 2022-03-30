#pragma once 

#include "node.hpp"

template <class T>
/// <summary>
/// Defines the structure of the AVL Tree.
/// </summary>
/// <typeparam name="T">A template class.</typeparam>
class AVLTree {
	/// <summary>
	/// Points to the root node of the AVL Tree.
	/// </summary>
	Node<T>* root_;

	/// <summary>
	/// Function to insert a node into the AVL Tree.
	/// </summary>
	/// <param name="root">Pointer to the root node of the AVL Tree.</param>
	/// <param name="data">The data of the node to be inserted into the AVL Tree.</param>
	/// <returns>A pointer to the newly node inserted into the AVL Tree.</returns>
	Node<T>* insertNode(Node<T>* root, T val) {

		// Normal BST insertion

		if (root == nullptr)
			root = new Node<T>(val);
		else if (val == root->data)
			return root;
		else if (val < root->data)
			root->leftChild = insertNode(root->leftChild, val);
		else
			root->rightChild = insertNode(root->rightChild, val);

		//To check if the node is unbalanced we use the balance factor of the ancestor 
		// 4 Cases if the node becomes unbalanced 
		// i) Left Left ii) Right Right iii) Left Right iv) Right Left

		if (balanceFactor(root) > 1) {
			if (val < root->leftChild->data)			// Left Left Case
				root = RR(root);
			else {								// Left Right Case
				root->leftChild = LR(root->leftChild);
				root = RR(root);
			}
		}
		else if (balanceFactor(root) < -1) {
			if (val < root->rightChild->data) {		// Right Left Case
				root->rightChild = RR(root->rightChild);
				root = LR(root);
			}
			else								// Right Right Case
				root = LR(root);
		}
		return root;
	}

	/// <summary>
	/// Function to calculate the balance factor of a node in the AVL Tree.
	/// </summary>
	/// <param name="root">Pointer to the node in the AVL Tree.</param>
	/// <returns>The balance factor data of the node in the AVL Tree.</returns>
	int balanceFactor(Node<T>* root) {
		int b = 0;
		if (root)
			b = height(root->leftChild) - height(root->rightChild);
		return b;
	}
	
	/// <summary>
	/// Function to calculate the height of a node in the AVL Tree.
	/// </summary>
	/// <param name="root">Pointer to the node in the AVL Tree.</param>
	/// <returns>The height of the node in the AVL Tree.</returns>
	int height(Node<T>* root) {
		int h = 0;
		if (root) {		// if root is not NULL then add the maximum of leftChild and rightChild subtree heights and add 1 to it to find the height
			int left = height(root->leftChild);
			int right = height(root->rightChild);
			h = 1 + ((left > right) ? left : right);
		}
		return h;
	}

	/// <summary>
	/// Function to rightChild rotate the AVL Tree at the given node.
	/// </summary>
	/// <param name="root">Pointer to the node of the AVL Tree.</param>
	/// <returns>The new root node at the point of rotation in the AVL Tree.</returns>
	Node<T>* RR(Node<T>* root) {
		Node<T>* l = root->leftChild;
		root->leftChild = l->rightChild;	// performing the rotation
		l->rightChild = root;
		return l;	// return the new root
	}
	
	/// <summary>
	/// Function to leftChild rotate the AVL Tree at the given node.
	/// </summary>
	/// <param name="root">Pointer to the node of the AVL Tree.</param>
	/// <returns>The new root node at the point of rotation in the AVL Tree.</returns>
	Node<T>* LR(Node<T>* root)
	{
		Node<T>* r = root->rightChild;
		root->rightChild = r->leftChild;	// performing the rotation
		r->leftChild = root;
		return r;	// return the new root
	}

	/// <summary>
	/// Function to find the maximum element in the AVL Tree.
	/// </summary>
	/// <param name="root">The root node of the AVL Tree.</param>
	/// <returns>The pointer to the maximum valued node in the AVL Tree.</returns>
	Node<T>* findMax(Node<T>* root)
	{
		if (root->rightChild == nullptr)	// If the rightChild end of the tree is reached return the maximum
			return root;
		else			// else keep traversing till the bottom rightChild end of the tree
			return findMax(root->rightChild);
	}

	/// <summary>
	/// Function to remove a node in the AVL Tree.
	/// </summary>
	/// <param name="root">The root node of the AVL Tree.</param>
	/// <param name="data">The data of the node to be removed in the AVL Tree.</param>
	/// <returns>The pointer to the new node at the deleted position in the AVL Tree.</returns>
	Node<T>* removeNode(Node<T>* root, T val)
	{
		if (root == nullptr)	// If the current root is empty return 
			return nullptr;

		if (val < root->data)	// if data is less than the current root search on the leftChild half of the tree recursively
			root->leftChild = removeNode(root->leftChild, val);
		else if (val > root->data)	// if data is greater than the current node's data, search on the rightChild half recursively
			root->rightChild = removeNode(root->rightChild, val);
		else {		// If the data to be removed is equal to the current root's data delete the node
			if (root->leftChild == nullptr && root->rightChild == nullptr) { // if the node to be removed is a leaf node
				delete root;
				return nullptr;
			}
			else if (root->leftChild == nullptr && root->rightChild != nullptr) {
				Node<T>* sub_right_tree = root->rightChild;   // Copying the rightChild subtree before deleting the current node
				delete root;
				return sub_right_tree;		// Return the pointer to the rightChild subtree
			}
			else if (root->leftChild != nullptr && root->rightChild == nullptr) {
				Node<T>* sub_left_tree = root->leftChild;  // Copying the leftChild subtree before deleting the current node
				delete root;
				return sub_left_tree;		// Return the pointer to the leftChild subtree
			}
			else			// if the node has both leftChild and rightChild subtrees find the maximum valued node in the leftChild subtree
						// and recursively call the removeNode function over leftChild subtree and data to be removed as the maximum of the leftChild subtree node
			{
				Node<T>* maxium_node_in_sub_left_tree = findMax(root->leftChild);
				root->data = maxium_node_in_sub_left_tree->data;
				root->leftChild = removeNode(root->leftChild, maxium_node_in_sub_left_tree->data);
			}
		}
		// Deletion may disturb the balance factor of the tree
		// To rebalance the tree perform leftChild or rightChild rotation
		if (balanceFactor(root) > 1) {
			if (height(root->leftChild->leftChild) > height(root->leftChild->rightChild)) {
				root = RR(root);
			}
			else {
				root->leftChild = LR(root->leftChild);
				root = RR(root);
			}
		}
		else if (balanceFactor(root) < -1) {
			if (height(root->rightChild->leftChild) > height(root->rightChild->rightChild)) {
				root->rightChild = RR(root->rightChild);
				root = LR(root);
			}
			else {
				root = LR(root);
			}
		}
		return root;
	}

	/// <summary>
	/// Function to search for a node in the AVL Tree.
	/// </summary>
	/// <param name="root">The root node of the AVL Tree.</param>
	/// <param name="data">The data of the node to be searched for in the AVL Tree.</param>
	/// <returns>The pointer to the node, if found, in the AVL Tree.</returns>
	Node<T>* searchNode(Node<T>* root, T val) {
		if (root == nullptr)	//if the tree is empty return the NULL pointer
			return nullptr;

		if (root->data == val)   // if the data is found at the current node return the node
			return root;
		else if (val < root->data) // If data to be searched is less the the current node's data search on the leftChild subtree
			return searchNode(root->leftChild, val);
		else    // If data to be searched is greater the the current node's data search on the rightChild subtree
			return searchNode(root->rightChild, val);
	}

	/// <summary>
	/// Function to delete all the nodes in the AVL Tree.
	/// </summary>
	/// <param name="root">The root node of the AVL Tree.</param>
	void clearTree(Node<T>* root) {
		if (root == nullptr) // if the root is empty return the function call 
			return;
		// recurvisely call and clear the leftChild and rightChild subtrees
		clearTree(root->leftChild);
		clearTree(root->rightChild);
		delete root; // then delete the current node after clear the subtrees
	}

	/// <summary>
	/// Function to remove the elements of one AVL Tree from another.
	/// </summary>
	/// <param name="node">The root node of the second AVL Tree.</param>
	void diff(Node<T>* node) {
		if (node == nullptr)
			return;
		remove(node->data);
		diff(node->leftChild);
		diff(node->rightChild);
	}

	/// <summary>
	/// Function to print the inorder traversal of the AVL Tree.
	/// </summary>
	/// <param name="root">The root node of the AVL Tree.</param>
	void inorder(Node<T>* root)
	{
		if (root == nullptr)
			return;
		inorder(root->leftChild);		// Traverse the Left half of the tree from the current node
		std::cout << root->data << ' ';	//Print the current node's data
		inorder(root->rightChild);	// Traverse the Right half of the tree from the current node
	}

	/// <summary>
	/// Function to print the preorder traversal of the AVL Tree.
	/// </summary>
	/// <param name="root">The root node of the AVL Tree.</param>
	void preorder(Node<T>* root)
	{
		if (root == nullptr)
			return;
		std::cout << root->data << ' ';    //Print the current node's data
		preorder(root->leftChild);	// Traverse the Left half of the tree from the current node
		preorder(root->rightChild);	// Traverse the Right half of the tree from the current node
	}

	/// <summary>
	/// Function to print the postorder traversal of the AVL Tree.
	/// </summary>
	/// <param name="root">The root node of the AVL Tree.</param>
	void postorder(Node<T>* root)
	{
		if (root == nullptr)
			return;
		postorder(root->leftChild);	// Traverse the Left half of the tree from the current node
		postorder(root->rightChild);	// Traverse the Right half of the tree from the current node
		std::cout << root->data << ' ';    //Print the current node's data
	}

	// Helper functions related to the AVL tree data structure
	// insert() - to insert a Node in the tree
	// getRoot()- returns the root of the tree
	// remove()- to remove a node with data provided to the function
	// display()- to print the inorder traversal of the tree
	//clear()- to delete the entire tree
	//difference()- 
	//search()- to find if a given data is in the tree or not
public:

	/// <summary>
	/// Constructor to initialize the AVL Tree.
	/// </summary>
	AVLTree() {
		root_ = nullptr;
	}

	/// <summary>
	/// Function to get the root node of the AVL Tree.
	/// </summary>
	/// <returns>The root node of the AVL Tree.</returns>
	Node<T>* getRoot() {
		return root_;
	}

	/// <summary>
	/// Helper function to insert a node into the AVL Tree.
	/// </summary>
	/// <param name="data">The data of the node to be inserted into the AVL Tree.</param>
	void insert(T val)
	{
		root_ = insertNode(root_, val);
	}

	/// <summary>
	/// Helper function to remove a node from the AVL Tree.
	/// </summary>
	/// <param name="data">The data of the node to be removed from the AVL Tree.</param>
	void remove(T val)
	{
		root_ = removeNode(root_, val);
	}

	/// <summary>
	/// Function to print the AVL Tree.
	/// </summary>
	void display()
	{
		inorder(root_);
		std::cout << std::endl;
	}

	/// <summary>
	/// Helper function to delete all nodes in the AVL Tree.
	/// </summary>
	void clear() {
		clearTree(root_);
		root_ = nullptr;
	}

	/// <summary>
	/// Helper function to delete the elements of one AVL Tree from another.
	/// </summary>
	/// <param name="t">The other AVL Tree, whose elements must be removed from the current one.</param>
	void difference(AVLTree<T>& t) {
		diff(t.getRoot());
	}

	/// <summary>
	/// Helper function to search the AVL Tree.
	/// </summary>
	/// <param name="data">The data of the node to be searched for in the AVL Tree.</param>
	/// <returns>The pointer to the matched node in the AVL Tree.</returns>
	Node<T>* search(T val) {
		return searchNode(root_, val);
	}
};