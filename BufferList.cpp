#include "BufferList.h"

BufferList::BufferList() {
	size = 0;
	head = new Node(0);
	head->next = head;
	head->prev = head;
}

BufferList::BufferList(const BufferList &copy) {
	size = copy.size;
	head = new Node(0);
	head->next = head;
	head->prev = head;
	Node *countCopy = copy.head->next;
	Node *temp = head;
	for (int i = 1; i < size; i++) {
		temp->next = new Node(countCopy->data);
		temp->next->prev = head;
		temp = temp->next;
		countCopy = countCopy->next;
	}
	temp->next = head;
	head->prev = temp;
}

BufferList::BufferList(BufferList &&copy) noexcept {
	size = copy.size;
	std::swap(head, copy.head);
}

BufferList &BufferList::operator=(const BufferList &copy) {
	if (this == &copy) {
		return *this;
	}
	makeEmpty();
	Node *countCopy = copy.head->next;
	Node *temp = head;
	size = copy.size;
	for (int i = 1; i < size; i++) {
		temp->next = new Node(countCopy->data);
		temp->next->prev = temp;
		temp = temp->next;
		countCopy = countCopy->next;
	}
	temp->next = head;
	head->prev = temp;
	return *this;
}

BufferList &BufferList::operator=(BufferList &&copy) noexcept {
	makeEmpty();
	size = copy.size;
	std::swap(head, copy.head);
	delete copy.head;
	return *this;
}

BufferList::~BufferList() {
	makeEmpty();
	delete head;
}

void BufferList::addElem(const T &elem, Iterator &iter) {
	size++;
	Node *tempNode = new Node(elem, iter.getNow()->next, iter.getNow());
	iter.getNow()->next->prev = tempNode;
	iter.getNow()->next = tempNode;
}

void BufferList::deleteElem(Iterator &iter) {
	if (iter.getNow() == head) {
		throw BufferException();
	}
	Node *delElem = iter.getNow();
	iter.next();
	delElem->next->prev = delElem->prev;
	delElem->prev->next = delElem->next;
	delete delElem;
	size--;
}

void BufferList::makeEmpty() {
	head = head->next;
	for (int i = 0; i < size; i++) {
		head = head->next;
		delete head->prev;
	}
	head->next = head;
	head->prev = head;
	size = 0;
}

bool BufferList::isEmpty() const {
	return size == 0;
}

int BufferList::getSize() const {
	return size;
}

Iterator *BufferList::findElem(const T &elem) {
	auto *listIterator = new BufferListIterator(this);
	listIterator->next();
	while (listIterator->getElement() != elem && !listIterator->finish()) {
		listIterator->next();
	}
	if (listIterator->getElement() != elem) {
		throw NoElemException();
	}
	return listIterator;
}

Iterator *BufferList::getIterator() {
	return new BufferListIterator(this);
}

///////////////////////////////////////

BufferList::BufferListIterator::BufferListIterator(BufferList *list) {
	this->list = list;
	this->nowPointer = list->head;
}

void BufferList::BufferListIterator::start() {
	nowPointer = list->head;
}

T BufferList::BufferListIterator::getElement() const {
	if (nowPointer == list->head) {
		throw BufferException();
	}
	return nowPointer->data;
}

void BufferList::BufferListIterator::next() {
	nowPointer = nowPointer->next;
}

void BufferList::BufferListIterator::prev() {
	nowPointer = nowPointer->prev;
}

bool BufferList::BufferListIterator::finish() const {
	return nowPointer->next == list->head;
}

Node *BufferList::BufferListIterator::getNow() const {
	return nowPointer;
}