#pragma once
#include "Node.h";

template<typename T>
class IIterator {
public:
	virtual void begin() = 0;//������ ������
	virtual T getValue() = 0;//�������� �������
	virtual void next() = 0;//�������� ������
	virtual bool hasNext() = 0;//�������� ��� �� ��������������
	virtual Node<T> *getNode() = 0;//�������� �������� �� ������ �������
};