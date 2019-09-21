#pragma once
#include <iostream>
#include <cstring>

class Dictionary {
private:
	struct Node {
		const char* word;
		int count;

		Node *left, *right;
		Node *parent;

		Node(const char *word, Node *parent = nullptr) : left(nullptr), right(nullptr), parent(nullptr)
		{
			count = 1;
			this->word = word;
		};
	};

	Node *root;

public:
	Dictionary() : root(nullptr) {};

	~Dictionary() {
		destroy(root);
	}

	Dictionary &operator=(const Dictionary &right) {
		if (this != &right) {
			destroy(root);
			root = new Node(right.root->word);
			copy(right.root, root);
		}
	}

	void insert(const char *word) {
		if (root == nullptr) {
			root = new Node(word);
			return;
		}

		Node *prev = nullptr;
		Node *curr = root;

		while (curr != nullptr) {
			if (strcmp(word, curr->word) > 0) {
				prev = curr;
				curr = curr->right;
			}
			else {
				if (strcmp(word, curr->word) < 0) {
					prev = curr;
					curr = curr->left;
				}
				else {
					if (strcmp(word, curr->word) == 0) {
						curr->count += 1;
						return;
					}
				}
			}
		}

		if (strcmp(word, prev->word) > 0)
			prev->right = new Node(word, prev);
		if (strcmp(word, prev->word) < 0)
			prev->left = new Node(word, prev);
	}

	friend std::ostream &operator<<(std::ostream &os, const Dictionary &dict) {
		return out(os, dict.root);
	}

	int find(const char *word) {
		Node *prev = nullptr;
		Node *curr = root;

		while (curr != nullptr) {
			if (strcmp(word, curr->word) > 0) {
				prev = curr;
				curr = curr->right;
			}
			else {
				if (strcmp(word, curr->word) < 0) {
					prev = curr;
					curr = curr->left;
				}
				else {
					if (strcmp(word, curr->word) == 0) {
						return curr->count;
					}
				}
			}
		}
		return 0;
	}

	bool isBinaryTree() {
		return check(root, minimum(root)->word, maximum(root)->word);
	}

	void deleteWord(const char *word) {
		deleteWord(root, word);
	}

	int wordsCount() {
		return wordsCount(root);
	}

private:
	static std::ostream &out(std::ostream &os, const Node *node) {
		if (node == nullptr)
			return os;

		out(os, node->left);
		os << node->word << "->count = " << node->count << std::endl;
		out(os, node->right);
		return os;
	}

	Node* deleteWord(Node* node, const char *word) {
		if (node == nullptr)
			return node;

		if (node->count > 1) {
			if (strcmp(word, node->word) == 0) {
				node->count -= 1;
				return node;
			}
		}

		if (strcmp(word, node->word) < 0)
			node->left = deleteWord(node->left, word);
		else
			if (strcmp(word, node->word) > 0)
				node->right = deleteWord(node->right, word);
			else
				if (node->left != nullptr && node->right != nullptr) {
					node->word = minimum(node->right)->word;
					node->right = deleteWord(node->right, word);
				}
				else
					if (node->left != nullptr)
						node = node->left;
					else
						node = node->right;
		return node;
	}

	Node* minimum(Node* node) {
		if (node->left == nullptr)
			return node;
		return minimum(node->left);
	}

	Node* maximum(Node* node) {
		if (node->right == nullptr)
			return node;
		return maximum(node->right);
	}

	bool check(Node *node, const char *min, const char *max) {
		if (node == nullptr)
			return true;

		if (strcmp(min, node->word) > 0 && strcmp(max, node->word) < 0)
			return false;

		return
			check(node->left, min, node->word) &&
			check(node->right, node->word, max);
	}

	int wordsCount(Node* node) {
		if (node == nullptr)
			return 0;

		return wordsCount(node->left) + node->count + wordsCount(node->right);
	}

	void destroy(Node *node) {
		if (node == nullptr)
			return;
		destroy(node->left);
		destroy(node->right);
		node->left = nullptr;
		node->right = nullptr;
		delete node;
	}

	void copy(Node *source, Node *dest) {
		if (source == nullptr)
			return;

		if (source->left != nullptr) {
			dest->left = new Node(source->left->word, dest);
			dest->left->count = source->left->count;
			copy(source->left, dest->left);
		}

		if (source->right != nullptr) {
			dest->right = new Node(source->right->word, dest);
			dest->right->count = source->right->count;
			copy(source->right, dest->right);
		}
	}
};