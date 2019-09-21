#pragma once
#include <iostream>
#include <string>

const int DEFAULT_CAPACITY = 16;

class HashTable
{

private:

	struct Entry {
		int key;
		int hash;
		std::string value;
		Entry *next;
	};

private:
	Entry **arr; 
	int capacity;
	int size; 
	int(*hash)(int); 
	bool(*areEqual)(int, int); 

public:
	class Iterator {
	private:
		HashTable *table;
		Entry *current;
		int cursor;
	public:

		Iterator(HashTable *tbl) {
			table = tbl;
		}

		void start() {
			cursor = 0;

			while (table->arr[cursor] == nullptr && cursor < table->capacity) {
				cursor++;
			}

			if (cursor == table->capacity - 1) {
				cursor = 0;
				current = nullptr;
			}
			else {
				current = table->arr[cursor];
			}
		}

		void next() {
	 		if (current->next != nullptr) {
				current = current->next;
			}
			else {
				cursor++;

				while (table->arr[cursor] == nullptr && cursor < table->capacity) {
					cursor++;
				}

				if (cursor == table->capacity) {
					cursor = 0;
					current = nullptr;
				}
				else
					current = table->arr[cursor];
			}
		}

		bool hasNext() {
			if (current == nullptr) {
				return false;
			}
			if (current->next != nullptr) {
				return true;
			}
			else {
				int temp = cursor + 1;
				while (table->arr[temp] == nullptr && temp < table->capacity)
					temp++;
				return temp != table->capacity;
			}
		}

		std::string getValue() {
			return current->value;
		}

		int getKey() {
			return current->key;
		}

		int getHash() {
			return current->hash;
		}

		Entry * getEntry() {
			return current;
		}
	};

public:

	HashTable(int(*hash)(int), bool(*areEqual)(int, int), int capacity = DEFAULT_CAPACITY) {
		size = 0;
		this->hash = hash;
		this->areEqual = areEqual;
		this->capacity = capacity;

		arr = new Entry *[capacity];
		for (int i = 0; i < capacity; i++)
			arr[i] = nullptr;
	};

	~HashTable()
	{};
	
	//проверка таблицы на пустоту 
	bool isEmpty() {  
		return size == 0;
	}

	//добавить элемент 
	void put(int key, std::string elem) { 
		int keyHash = hash(key);
		int pos = keyHash % capacity;

		Entry *entr = new Entry;
		entr->value = elem;
		entr->key = key;
		entr->hash = keyHash;
		entr->next = nullptr;
		if (size == (int)(capacity * 0.75)) {
			resize(capacity * 2);
		}
		if (arr[pos] != nullptr) {
			if (arr[pos]->key == key) {
				arr[pos]->value = entr->value;
				arr[pos]->hash = entr->hash;
			}
			else {
				Entry *temp = new Entry;
				temp = arr[pos];

				while (temp->next != nullptr) {
					temp = temp->next;
				}
				temp->next = entr;
			}
		}
		else {
			arr[pos] = entr;
			size++;
		}
	}

	//удалить элемент
	void remove(int key) {    
		int keyHash = hash(key);
		int pos = keyHash % capacity;
		if (arr[pos]->next != nullptr) {
			if (arr[pos]->key == key) {
				arr[pos] = arr[pos]->next;
			}
			else {
				Entry *temp = new Entry;
				temp = arr[pos];

				while (temp->next != nullptr) {
					if (temp->next->key == key) {
						if (temp->next->next != nullptr) {
							temp->next = temp->next->next;
						}
						else {
							temp->next = nullptr;
						}
					}
				}
			}
		}
		else {
			arr[pos] = nullptr;
			size--;
		}
	}

	//найти элемент
	std::string findElem(int key) { 
		int keyHash = hash(key);
		int pos = keyHash % capacity;
		if (arr[pos] != nullptr) {
			Entry *temp = new Entry;
			temp = arr[pos];

			while (temp->next != nullptr) {
				if (temp->key == key) {
					return temp->value;
				}
				temp = temp->next;
			}
		}
		return nullptr;
	}

	//сделать таблицу пустой
	void makeEmpty() {
		for (int i = 0; i < capacity; i++) {
			Entry *entry = arr[i];
			Entry *next = nullptr;
			while (entry != nullptr) {
				next = entry->next;
				delete entry;
				entry = next;
			}
		}
		size = 0;
	}

	Iterator getIterator() {
		return Iterator(this);
	}

	int getCap() {
		return capacity;
	}

	//вывод таблицы
	void print() {    
		Iterator iter = getIterator();
		iter.start();
		if (size > 0) {
			std::cout << iter.getValue() << std::endl;
			while (iter.hasNext()) {
				iter.next();
				std::cout << iter.getValue() << std::endl;
			}
		}
		std::cout << std::endl;
	}

private:
	void resize(int newCap) {
		Entry **newArr = new Entry *[newCap];
		for (int i = 0; i < newCap; i++)
			newArr[i] = nullptr;

		int pos;

		size = 0;

		Iterator it = this->getIterator();
		it.start();

		Entry *temp;
		Entry *curr;

		while (it.hasNext()) {
			temp = it.getEntry();
			temp->next = nullptr;
			pos = temp->hash % newCap;

			if (newArr[pos] != nullptr) {
				curr = newArr[pos];
				while (curr->next != nullptr) {
					curr = curr->next;
				}
				curr->next = temp;
			}
			else {
				newArr[pos] = temp;
				size++;
			}
			it.next();
		}
		delete[] arr;
		arr = newArr;
		capacity = newCap;
	}
};