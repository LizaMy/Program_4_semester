#pragma once
#include"IIterator.h"

template <typename T>
class IList
{
public:

	virtual void insert(T elem, IIterator<T>* iterator) = 0;//вставить элемент
	virtual void remove(IIterator<T>* iterator) = 0;//удалить элемент
	virtual IIterator<T>* findFirst(T elem) = 0;//найти первое вхождение элемента в список
	virtual void clear() = 0;//сделать пустым
	virtual bool isEmpty() = 0;//проверка на пустоту
	virtual int getSize() = 0;//кол-во элементов 
	virtual IIterator<T>* getIterator() = 0;//получить итератор
};
