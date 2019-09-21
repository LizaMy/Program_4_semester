#pragma once
#include "Node.h";

template<typename T>
class IIterator {
public:
	virtual void begin() = 0;//начать работу
	virtual T getValue() = 0;//получить элемент
	virtual void next() = 0;//сдвинуть вправо
	virtual bool hasNext() = 0;//проверка все ли проитерировано
	virtual Node<T> *getNode() = 0;//получить итератор на первый элемент
};