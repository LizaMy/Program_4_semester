#ifndef EXC_LIST_H
#define EXC_LIST_H
#include "Iterator.h"

struct BufferException {};
struct NoElemException {};

class List {
public:
	virtual void addElem(const T &elem, Iterator &iter) = 0;
	virtual void deleteElem(Iterator &iter) = 0;
	virtual void makeEmpty() = 0;
	virtual bool isEmpty() const = 0;
	virtual int getSize() const = 0;
	virtual Iterator* findElem(const T &elem) = 0;
	virtual Iterator* getIterator() = 0;
};

#endif
