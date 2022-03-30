template <class T>
/// <summary>
/// Defines the structure of an AVL Tree Node.
/// </summary>
/// <typeparam name="T">A template class.</typeparam>
class Node {
public:
	/// <summary>
	/// Stores the data of the node.
	/// </summary>
	T data;
	/// <summary>
	/// Pointer to the leftChild child of the node.
	/// </summary>
	Node* leftChild;
	/// <summary>
	/// Pointer to the rightChild child of the node.
	/// </summary>
	Node* rightChild;

	/// <summary>
	/// Constructor to initialize the AVL Tree Node.
	/// </summary>
	/// <param name="data">The data of the node being initialized.</param>
	Node(T value) {
		this->data = value;
		this->leftChild = nullptr;
		this->rightChild = nullptr;
	}
};