#include <iostream>
#include "BufferList.h"

int main() {
	BufferList *firstBL = new BufferList();
	BufferList::BufferListIterator itr(firstBL);
	firstBL->addElem(1, itr);
	itr.next();
	firstBL->addElem(3, itr);
	firstBL->addElem(2, itr);
	itr.start();
	while (!itr.finish()) {
		itr.next();
		std::cout << itr.getElement() << std::endl;
	}
	std::cout << "--------------------------------" << std::endl;
	Iterator *itr2 = firstBL->getIterator();
	itr2->next();
	std::cout << itr2->getElement() << std::endl;
	Iterator *itr3 = firstBL->findElem(3);
	firstBL->deleteElem(*itr3);
	itr.start();
	std::cout << "--------------------------------" << std::endl;
	while (!itr.finish()) {
		itr.next();
		std::cout << itr.getElement() << std::endl;
	}
	std::cout << "--------------------------------" << std::endl;
	std::cout << "Size: " << firstBL->getSize() << std::endl;
	std::cout << "isEmpty: " << firstBL->isEmpty() << std::endl;
	firstBL->makeEmpty();
	std::cout << "isEmpty: " << firstBL->isEmpty() << std::endl;
	itr.start();
	std::cout << "--------------------------------" << std::endl;
	while (!itr.finish()) {
		itr.next();
		std::cout << itr.getElement() << std::endl;
	}
	system("pause");
	return 0;
}