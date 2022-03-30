template <class T>
/// <summary>
/// Defines the structure of an AVL Tree Node.
/// </summary>
/// <typeparam name="T">A template class.</typeparam>
class AVLNode {
public:
	/// <summary>
	/// Stores the value of the node.
	/// </summary>
	T val;
	/// <summary>
	/// Pointer to the left child of the node.
	/// </summary>
	AVLNode* left;
	/// <summary>
	/// Pointer to the right child of the node.
	/// </summary>
	AVLNode* right;

	/// <summary>
	/// Constructor to initialize the AVL Tree Node.
	/// </summary>
	/// <param name="val">The value of the node being initialized.</param>
	AVLNode(T val) {
		this->val = val;
		this->left = nullptr;
		this->right = nullptr;
	}
};