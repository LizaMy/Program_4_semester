#include "HashTable.h";
#include <iostream>;


int main() {
	setlocale(LC_ALL, "Russian");
	HashTable table([](int i) -> int { return i; }, [](int i, int j) -> bool { return i == j; });

	table.put(4, "aaa");
	table.put(20, "bbbbbbb");
	table.put(40, "CCCCCC");
	

	std::cout << "Исходная таблица: " << std::endl;
	table.print();
	std::cout << "===============================" << std::endl;


	table.remove(40);
	std::cout << "Удалить элемент: " << std::endl;
	table.print();


	std::cout << "===============================" << std::endl;
	std::cout << "Найти элемент" << std::endl;
	std::cout << table.findElem(4) << std::endl << std::endl;

	std::cout << "===============================" << std::endl;
	std::cout << "Сделать таблицу пустой" << std::endl;
	if (!table.isEmpty()) 
	{
		table.makeEmpty();
	}

	table.print();

	system("pause");
	return 0;
}