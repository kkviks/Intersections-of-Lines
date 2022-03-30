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
	AVLNode<T>* root_;

	/// <summary>
	/// Function to insert a node into the AVL Tree.
	/// </summary>
	/// <param name="root">Pointer to the root node of the AVL Tree.</param>
	/// <param name="val">The value of the node to be inserted into the AVL Tree.</param>
	/// <returns>A pointer to the newly node inserted into the AVL Tree.</returns>
	AVLNode<T>* insertNode(AVLNode<T>* root, T val) {

		// Normal BST insertion

		if (root == nullptr)
			root = new AVLNode<T>(val);
		else if (val == root->val)
			return root;
		else if (val < root->val)
			root->left = insertNode(root->left, val);
		else
			root->right = insertNode(root->right, val);

		//To check if the node is unbalanced we use the balance factor of the ancestor 
		// 4 Cases if the node becomes unbalanced 
		// i) Left Left ii) Right Right iii) Left Right iv) Right Left

		if (balanceFactor(root) > 1) {
			if (val < root->left->val)			// Left Left Case
				root = RR(root);
			else {								// Left Right Case
				root->left = LR(root->left);
				root = RR(root);
			}
		}
		else if (balanceFactor(root) < -1) {
			if (val < root->right->val) {		// Right Left Case
				root->right = RR(root->right);
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
	/// <returns>The balance factor value of the node in the AVL Tree.</returns>
	int balanceFactor(AVLNode<T>* root) {
		int b = 0;
		if (root)
			b = height(root->left) - height(root->right);
		return b;
	}
	
	/// <summary>
	/// Function to calculate the height of a node in the AVL Tree.
	/// </summary>
	/// <param name="root">Pointer to the node in the AVL Tree.</param>
	/// <returns>The height of the node in the AVL Tree.</returns>
	int height(AVLNode<T>* root) {
		int h = 0;
		if (root) {		// if root is not NULL then add the maximum of left and right subtree heights and add 1 to it to find the height 
			int left = height(root->left);
			int right = height(root->right);
			h = 1 + ((left > right) ? left : right);
		}
		return h;
	}

	/// <summary>
	/// Function to right rotate the AVL Tree at the given node.
	/// </summary>
	/// <param name="root">Pointer to the node of the AVL Tree.</param>
	/// <returns>The new root node at the point of rotation in the AVL Tree.</returns>
	AVLNode<T>* RR(AVLNode<T>* root) {
		AVLNode<T>* l = root->left;
		root->left = l->right;	// performing the rotation
		l->right = root;
		return l;	// return the new root
	}
	
	/// <summary>
	/// Function to left rotate the AVL Tree at the given node.
	/// </summary>
	/// <param name="root">Pointer to the node of the AVL Tree.</param>
	/// <returns>The new root node at the point of rotation in the AVL Tree.</returns>
	AVLNode<T>* LR(AVLNode<T>* root)
	{
		AVLNode<T>* r = root->right;
		root->right = r->left;	// performing the rotation
		r->left = root;
		return r;	// return the new root
	}

	/// <summary>
	/// Function to find the maximum element in the AVL Tree.
	/// </summary>
	/// <param name="root">The root node of the AVL Tree.</param>
	/// <returns>The pointer to the maximum valued node in the AVL Tree.</returns>
	AVLNode<T>* findMax(AVLNode<T>* root)
	{
		if (root->right == nullptr)	// If the right end of the tree is reached return the maximum
			return root;
		else			// else keep traversing till the bottom right end of the tree
			return findMax(root->right);
	}

	/// <summary>
	/// Function to remove a node in the AVL Tree.
	/// </summary>
	/// <param name="root">The root node of the AVL Tree.</param>
	/// <param name="val">The value of the node to be removed in the AVL Tree.</param>
	/// <returns>The pointer to the new node at the deleted position in the AVL Tree.</returns>
	AVLNode<T>* removeNode(AVLNode<T>* root, T val)
	{
		if (root == nullptr)	// If the current root is empty return 
			return nullptr;

		if (val < root->val)	// if value is less than the current root search on the left half of the tree recursively 
			root->left = removeNode(root->left, val);
		else if (val > root->val)	// if value is greater than the current node's value, search on the right half recursively 
			root->right = removeNode(root->right, val);
		else {		// If the value to be removed is equal to the current root's value delete the node
			if (root->left == nullptr && root->right == nullptr) { // if the node to be removed is a leaf node 
				delete root;
				return nullptr;
			}
			else if (root->left == nullptr && root->right != nullptr) {
				AVLNode<T>* sub_right_tree = root->right;   // Copying the right subtree before deleting the current node
				delete root;
				return sub_right_tree;		// Return the pointer to the right subtree 
			}
			else if (root->left != nullptr && root->right == nullptr) {
				AVLNode<T>* sub_left_tree = root->left;  // Copying the left subtree before deleting the current node
				delete root;
				return sub_left_tree;		// Return the pointer to the left subtree 
			}
			else			// if the node has both left and right subtrees find the maximum valued node in the left subtree 
						// and recursively call the removeNode function over left subtree and value to be removed as the maximum of the left subtree node 
			{
				AVLNode<T>* maxium_node_in_sub_left_tree = findMax(root->left);
				root->val = maxium_node_in_sub_left_tree->val;
				root->left = removeNode(root->left, maxium_node_in_sub_left_tree->val);
			}
		}
		// Deletion may disturb the balance factor of the tree
		// To rebalance the tree perform left or right rotation 
		if (balanceFactor(root) > 1) {
			if (height(root->left->left) > height(root->left->right)) {
				root = RR(root);
			}
			else {
				root->left = LR(root->left);
				root = RR(root);
			}
		}
		else if (balanceFactor(root) < -1) {
			if (height(root->right->left) > height(root->right->right)) {
				root->right = RR(root->right);
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
	/// <param name="val">The value of the node to be searched for in the AVL Tree.</param>
	/// <returns>The pointer to the node, if found, in the AVL Tree.</returns>
	AVLNode<T>* searchNode(AVLNode<T>* root, T val) {
		if (root == nullptr)	//if the tree is empty return the NULL pointer
			return nullptr;

		if (root->val == val)   // if the value is found at the current node return the node 
			return root;
		else if (val < root->val) // If value to be searched is less the the current node's value search on the left subtree
			return searchNode(root->left, val);
		else    // If value to be searched is greater the the current node's value search on the right subtree
			return searchNode(root->right, val);
	}

	/// <summary>
	/// Function to delete all the nodes in the AVL Tree.
	/// </summary>
	/// <param name="root">The root node of the AVL Tree.</param>
	void clearTree(AVLNode<T>* root) {
		if (root == nullptr) // if the root is empty return the function call 
			return;
		// recurvisely call and clear the left and right subtrees
		clearTree(root->left);
		clearTree(root->right);
		delete root; // then delete the current node after clear the subtrees
	}

	/// <summary>
	/// Function to remove the elements of one AVL Tree from another.
	/// </summary>
	/// <param name="node">The root node of the second AVL Tree.</param>
	void diff(AVLNode<T>* node) {
		if (node == nullptr)
			return;
		remove(node->val);
		diff(node->left);
		diff(node->right);
	}

	/// <summary>
	/// Function to print the inorder traversal of the AVL Tree.
	/// </summary>
	/// <param name="root">The root node of the AVL Tree.</param>
	void inorder(AVLNode<T>* root)
	{
		if (root == nullptr)
			return;
		inorder(root->left);		// Traverse the Left half of the tree from the current node
		std::cout << root->val << ' ';	//Print the current node's value
		inorder(root->right);	// Traverse the Right half of the tree from the current node
	}

	/// <summary>
	/// Function to print the preorder traversal of the AVL Tree.
	/// </summary>
	/// <param name="root">The root node of the AVL Tree.</param>
	void preorder(AVLNode<T>* root)
	{
		if (root == nullptr)
			return;
		std::cout << root->val << ' ';    //Print the current node's value
		preorder(root->left);	// Traverse the Left half of the tree from the current node
		preorder(root->right);	// Traverse the Right half of the tree from the current node
	}

	/// <summary>
	/// Function to print the postorder traversal of the AVL Tree.
	/// </summary>
	/// <param name="root">The root node of the AVL Tree.</param>
	void postorder(AVLNode<T>* root)
	{
		if (root == nullptr)
			return;
		postorder(root->left);	// Traverse the Left half of the tree from the current node
		postorder(root->right);	// Traverse the Right half of the tree from the current node
		std::cout << root->val << ' ';    //Print the current node's value
	}

	// Helper functions related to the AVL tree data structure
	// insert() - to insert a Node in the tree
	// getRoot()- returns the root of the tree
	// remove()- to remove a node with value provided to the function
	// display()- to print the inorder traversal of the tree
	//clear()- to delete the entire tree
	//difference()- 
	//search()- to find if a given value is in the tree or not
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
	AVLNode<T>* getRoot() {
		return root_;
	}

	/// <summary>
	/// Helper function to insert a node into the AVL Tree.
	/// </summary>
	/// <param name="val">The value of the node to be inserted into the AVL Tree.</param>
	void insert(T val)
	{
		root_ = insertNode(root_, val);
	}

	/// <summary>
	/// Helper function to remove a node from the AVL Tree.
	/// </summary>
	/// <param name="val">The value of the node to be removed from the AVL Tree.</param>
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
	/// <param name="val">The value of the node to be searched for in the AVL Tree.</param>
	/// <returns>The pointer to the matched node in the AVL Tree.</returns>
	AVLNode<T>* search(T val) {
		return searchNode(root_, val);
	}
};