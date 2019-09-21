#pragma once
#include <iostream>
#include <vector>

class BinaryTree {
private:
	struct Node {
		int value;

		Node *left, *right;

		Node(int val) : value(val), left(nullptr), right(nullptr)
		{}
	};

	Node *root;

public:
	BinaryTree() : root(nullptr) {};

	~BinaryTree() {
		destroy(root);
	}

	BinaryTree &operator=(const BinaryTree &right) {
		if (this != &right) {
			root = new Node(right.root->value);
			copy(right.root, this->root);
		}

		return *this;
	}

	BinaryTree &operator=(BinaryTree &&right) {
		if (this != &right) {
			root = right.root;
			right.root = nullptr;
		}
	}

	void add(int elem, const char *path) {
		Node *temp = root;
		int len = strlen(path);

		if (root != nullptr) {
			for (int i = 0; i < len - 1; i++) {
				if (path[i] == '0') {
					if (temp->left != nullptr)
						temp = temp->left;
					else throw "invalid path";
				}
				else {
					if (temp->right != nullptr)
						temp = temp->right;
					else throw "invalid path";
				}
			}

			if (path[len - 1] == '0')
				temp->left = new Node(elem);
			else
				temp->right = new Node(elem);
		}
		else {
			if (path != "") throw "invalid path";
			this->root = new Node(elem);
		}
	}

	friend std::ostream &operator<<(std::ostream &os, const BinaryTree &tree) {
		std::cout << "If you want to print the tree in reverse order, enter 'r', else enter 'n'" << std::endl;
		char choise;
		std::cin >> choise;

		if (choise == 'n')
			return out(os, tree.root, 0);
		if (choise == 'r')
			return outReverse(os, tree.root, 0);
	}

	bool isPositive() {
		return  isPositive(root);
	}

	int countEven() {
		return countEven(root);
	}

	double average() {
		return sum(root) / count(root);
	}

	void delLeaves() {
		if (delLeaves(root))
			root = nullptr;
	}

	std::vector<char> find(int elem) {
		std::vector<char> res;

		if (find(res, root, elem))
			res.pop_back();
		else {
			res.clear();
			res.push_back('n');
		}
		return res;
	}

	bool find(std::vector<char> &accum, Node *node, int elem) {
		if (!accum.empty() && accum[accum.size() - 1] == 'q')
			return true;

		if (node == nullptr)
			return false;

		if (node->value == elem) {
			accum.push_back('q');
			return true;
		}

		if (node->left != nullptr) {
			if (!accum.empty() && accum[accum.size() - 1] == 'q')
				return true;

			accum.push_back('0');
			find(accum, node->left, elem);
		}

		if (node->right != nullptr) {
			if (!accum.empty() && accum[accum.size() - 1] == 'q')
				return true;

			accum.push_back('1');
			find(accum, node->right, elem);
		}

		if (node->right == nullptr && node->left == nullptr && !accum.empty() && accum[accum.size() - 1] != 'q')
			accum.clear();

		return false;
	}

	bool isBinaryTree() {
		return check(root, INT_MAX, INT_MIN);
	}

private:
	static std::ostream &out(std::ostream &os, Node *node, int space) {
		if (node == nullptr)
			return os;
		for (int i = 0; i < space; i++)
			os << " ";
		os << node->value << std::endl;
		out(os, node->left, space + 1);
		out(os, node->right, space + 1);
		return os;
	}

	static std::ostream &outReverse(std::ostream &os, Node *node, int space) {
		if (node == nullptr)
			return os;
		for (int i = 0; i < space; i++)
			os << " ";
		os << node->value << std::endl;
		out(os, node->right, space + 1);
		out(os, node->left, space + 1);
		return os;
	}

	bool isPositive(Node *node) {
		if (node == nullptr)
			return true;
		return isPositive(node->left) && (node->value >= 0) && isPositive(node->right);
	}

	int countEven(Node *node) {
		if (node == nullptr)
			return 0;
		return countEven(node->left) + (node->value % 2 == 0 ? 1 : 0) + countEven(node->right);
	}

	double sum(Node *node) {
		if (node == nullptr)
			return 0;
		return sum(node->left) + node->value + sum(node->right);
	}

	int count(Node *node) {
		if (node == nullptr)
			return 0;
		return count(node->left) + 1 + count(node->right);
	}

	bool delLeaves(Node *node) {
		if (node == nullptr)
			return false;

		if (!(node->left != nullptr || node->right != nullptr)) {
			delete node;
			return true;
		}
		else {
			if (delLeaves(node->left))
				node->left = nullptr;
			if (delLeaves(node->right))
				node->right = nullptr;
			return false;
		}
	}

	void copy(Node *source, Node *dest) {
		if (source == nullptr)
			return;

		if (source->left) {
			dest->left = new Node(source->left->value);
			copy(source->left, dest->left);
		}
		if (source->right) {
			dest->right = new Node(source->right->value);
			copy(source->right, dest->right);
		}
	}

	void destroy(Node *node) {
		if (!node) {
			return;
		}
		destroy(node->left);
		destroy(node->right);
		node->left = nullptr;
		node->right = nullptr;
		delete node;
	}

	bool check(Node *node, int min, int max) {
		if (node == nullptr)
			return true;

		if (node->value <= min || node->value >= max)
			return false;

		return
			check(node->left, min, node->value) &&
			check(node->right, node->value, max);
	}
};