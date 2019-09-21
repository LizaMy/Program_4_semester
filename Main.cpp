#include "Dictionary.h";
#include <iostream>;
#include <cstring>;

int main() {

	Dictionary *dictionary = new Dictionary();

	dictionary->insert("apple");
	dictionary->insert("pear");
	dictionary->insert("banana");
	dictionary->insert("orange");
	dictionary->insert("pineapple");
	dictionary->insert("banana");
	dictionary->insert("banana");
	dictionary->insert("apple");


	std::cout << *dictionary << std::endl;
	std::cout << "count words = " << dictionary->wordsCount() << std::endl;
	std::cout << "==========================================" << std::endl;

	dictionary->deleteWord("banana");
	dictionary->deleteWord("banana");
	dictionary->deleteWord("banana");

	std::cout << *dictionary << std::endl;
	std::cout << "count words = " << dictionary->wordsCount() << std::endl;
	std::cout << "==========================================" << std::endl;

	std::cout << "count of apple" << std::endl;
	std::cout << dictionary->find("apple") << std::endl;

	system("pause");
	return 0;
}