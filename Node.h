#pragma once

template<typename T>
struct Node
{
	T value;
	Node<T> *previous;
	Node<T> *next;
	Node(T value = T(), Node * previous = nullptr, Node * next = nullptr) {
		this->value = value;
		this->next = next;
		this->previous = previous;
	}
};