#ifndef EXC_ITERATOR_H
#define EXC_ITERATOR_H

#include "iostream"

typedef int T;
struct Node
{
	T data;
	Node *next;
	Node *prev;

	explicit Node(T data, Node* next = nullptr, Node* prev = nullptr) {
		this->data = data;
		this->next = next;
		this->prev = prev;
	}
};

class Iterator {
public:
	virtual void start() = 0;
	virtual T getElement() const = 0;
	virtual void next() = 0;
	virtual void prev() = 0;
	virtual bool finish() const = 0;   
	virtual Node* getNow() const = 0;
};

#endif