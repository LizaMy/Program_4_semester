#pragma once
#include"IIterator.h"

template <typename T>
class IList
{
public:

	virtual void insert(T elem, IIterator<T>* iterator) = 0;//�������� �������
	virtual void remove(IIterator<T>* iterator) = 0;//������� �������
	virtual IIterator<T>* findFirst(T elem) = 0;//����� ������ ��������� �������� � ������
	virtual void clear() = 0;//������� ������
	virtual bool isEmpty() = 0;//�������� �� �������
	virtual int getSize() = 0;//���-�� ��������� 
	virtual IIterator<T>* getIterator() = 0;//�������� ��������
};
