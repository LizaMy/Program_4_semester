#ifndef EXC_BUFFERLIST_H
#define EXC_BUFFERLIST_H
#include "List.h"
class BufferList : public List
{
private:
	Node* head;
	int size;

public:
	friend class BufferListIterator;
	class BufferListIterator : public Iterator {
	private:
		BufferList *list;
		Node * nowPointer;
	public:
		explicit BufferListIterator(BufferList *list);
		void start() override;
		T getElement() const override;
		void next() override;
		void prev() override;
		bool finish() const override;
		Node* getNow() const override;
	};
	void addElem(const T &elem, Iterator &iter) override;
	void deleteElem(Iterator &iter) override;
	void makeEmpty() override;
	bool isEmpty() const override;
	int getSize() const override;
	Iterator* findElem(const T &elem) override;
	Iterator* getIterator() override;
	BufferList();
	BufferList(const BufferList& copy);
	BufferList(BufferList&& copy) noexcept;
	BufferList& operator= (const BufferList &copy);
	BufferList& operator= (BufferList&& copy) noexcept;
	~BufferList();
};

#endif