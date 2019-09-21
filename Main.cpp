#include <iostream>
#include "List.h"

template<class T>
void print(IList<T> *list) {
	IIterator<T> *iter = list->getIterator();
	iter->begin();
	while (!iter->hasNext()) {
		std::cout << iter->getValue() << " ";
		iter->next();
	}
	std::cout << std::endl;
}

int main() {
	setlocale(LC_ALL, "ru");

	List<int> *list = new List<int>();
	IIterator<int> *iter = list->getIterator();

	list->insert(1, iter);    //��������� �������
	list->insert(2, iter);
	list->insert(3, iter);
	list->insert(4, iter);
	list->insert(5, iter);

	print<int>(list);

	printf("");

	iter = list->findFirst(1);       // ������ ��������� �������� � ������, ��������� � �������� �� ��������� �������
	
    list->insert(1, iter);      
	iter->next();   //����� ������
	list->insert(2, iter);
	iter->next();
	list->insert(3, iter);
	iter->next();
	list->insert(4, iter);
	iter->next();
	list->insert(5, iter);

	print<int>(list);

	iter = list->findFirst(2);
	list->remove(iter);    // ������� �������
	print<int>(list);

	list->clear();   //������ ������ ������
	list->isEmpty();
	printf("������: ");

	print<int>(list);

	system("pause");
	return 0;
}