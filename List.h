#include "IList.h"

template<typename T>
class List : public IList<T> {
private:

	template<typename TI>
	class Iterator : public IIterator<T> {
	private:
		List *list;
		Node<T> *cursor;
		bool finished;
	public:
		Iterator(List<TI> *list) {
			this->list = list;
			finished = false;
			cursor = list->buffer;
		}
		void begin() {
			cursor = list->buffer->next;
		}
		T getValue() {
			return cursor->value;
		}
		void next() {
			cursor = cursor->next;
			if (cursor == list->buffer)
			{
				cursor = cursor->next;
				finished = true;
			}
		}
		bool hasNext() {
			return finished;
		}
		Node<TI> *getNode() {
			return cursor;
		}
	};

	Node<T> *buffer;
	int size;

public:

	List()
	{
		buffer = new Node<T>();
		buffer->next = buffer;
		buffer->previous = buffer;
		size = 0;
	}

	~List()
	{
		clear();
	}

	void insert(T value, IIterator<T>* iterator) {
		Node<T> *node = new Node<T>();
		node->value = value;
		Node<T> *current = iterator->getNode();
		Node<T> *next = current->next;
		current->next = node;
		node->previous = current;
		next->previous = node;
		node->next = next;
		size++;
	}

	void remove(IIterator<T>* iterator) {
		Node<T> *current = iterator->getNode();
		if (current == buffer)
			throw "Can't remove buffer element.";
		Node<T> *next = current->next;
		Node<T> *previous = current->previous;
		next->previous = previous;
		previous->next = next;
		size--;
		delete current;
	}

	IIterator<T>* findFirst(T value) {
		IIterator<T> *iter = getIterator();
		iter->begin();
		while (!iter->hasNext()) {
			if (iter->getValue() == value)
				return iter;
			iter->next();
		}
		return iter;
	}

	void clear() {
		Node<T> *current, *next = buffer->next;
		for (int i = 0; i < size; i++) {
			current = next;
			next = current->next;
			delete current;
		}
		buffer->next = buffer;
		buffer->previous = buffer;
		size = 0;
	}

	bool isEmpty() {
		return size == 0;
	}

	int getSize() {
		return size;
	}

	IIterator<T>* getIterator() {
		return new Iterator<T>(this);
	}

};
