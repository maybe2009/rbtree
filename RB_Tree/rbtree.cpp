enum class NodeColor {RED, BLACK};

template<T>
struct Node {
	T val;
	NodeColor color;
	Node<T>* left;
	Node<T>* right;
	Node<T>* parent;
};

//caller should make sure that both fulcrum and fulcrum.right are not null
template<T>
void LeftRotate(Node<T>* fulcrum) {
	Node<T>* right_child = fulcrum->right;
	fulcrum->right = right_child->left;
	right_child->left = fulcrum;
}

//caller should make sure that both fulcrum and fulcrum.left are not null
template<T>
void RightRotate(Node<T>* fulcrum) {
	Node<T>* parent = fulcrum->parent;
	parent->left = fulcrum->right;
	fulcrum->right = parent;
}

template<T>
void Split(Node<T>* node) {
	node->left->color = NodeColor::BLACK;
	node->right->color = NodeColor::RED;
	node->color = NodeColor::RED;
}

template<T>
void InsertAsLeftChild(Node<T>* parent, Node<T>* left_child) {
	parent->left = left_child;
	left_child->parent = parent;
}

template<T>
void InsertAsRightChild(Node<T>* parent, Node<T>* right_child) {
	parent->right = right_child;
	right_child->parent = parent;
}

template<T>
void FixRB(Node<T>* new_node) {
	Node<T>* parent = new_node->parent;
	if (NodeColor::BLACK == parent->color) {
		if (nullptr == parent->left || nullptr == parent->right) {
			//parent has only one new red node
			if (parent->right == new_node) {
				LeftRotate(parent);
			}
		}
		else {
			//parent has a red left node
			Split(parent);
			FixRB(parent);
		}
	}
	else {
		Node<T>* fulcrum = parent;

		if (parent->right == new_node) {
			LeftRotate(parent);
			fulcrum = new_node;
		}

		RightRotate(fulcrum);
		Split(fulcrum);
		FixRB(fulcrum);
	}
}

template<T>
void Insert(Node<T>* root, Node<T>* node) {
	Node<T>* cur_node = root;
	while (true) {
		cur_node = cur_node->val >= node->right ? cur_node->right : cur_node->left;

		if (cur_node->val >= node->val) {
			if (cur_node->left == nullptr) {
				InsertAsLeftChild(cur_node, node);
				break;
			}
			else {
				cur_node = cur_node->left;
			}
		}
		else {
			if (cur_node->right == nullptr) {
				InsertAsRightChild(cur_node, node);
				break;
			}
			else {
				cur_node = cur_node->right;
			}
		}
	}
}