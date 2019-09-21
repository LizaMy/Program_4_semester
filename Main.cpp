#include "BinaryTreer.h";
#include <iostream>;

using namespace std;

int main() {

	BinaryTree *tree1 = new BinaryTree();
	BinaryTree *tree2 = new BinaryTree();

	try
	{
		tree1->add(1, "");
		tree1->add(1, "0");
		tree1->add(1, "00");
		tree1->add(2, "00");
		tree1->add(2, "1");
		tree1->add(21, "10");
		tree1->add(12, "11");

		cout << *tree1 << endl;

		tree2 = tree1;

		cout << *tree2 << endl;

	}
	catch (char *str)
	{
		std::cout << str << std::endl;
	}

	cout << endl << "====================================================" << endl;
	cout << "count of even" << endl;
	cout << tree1->countEven() << endl;

	cout << endl << "====================================================" << endl;
	cout << "check positive" << endl;
	if (tree1->isPositive())
	{
		cout << "true" << endl;

	}
	else
	{
		cout << "false" << endl;

	}

	cout << endl << "====================================================" << endl;
	cout << "average" << endl;
	cout << tree1->average() << endl;

	cout << endl << "====================================================" << endl;
	cout << "delete leaves" << endl;
	tree1->delLeaves();
	cout << *tree1 << endl;

	cout << endl << "====================================================" << endl;
	cout << "find 25" << endl;
	auto path = tree1->find(25);
	for (char c : path)
		std::cout << c;
	std::cout << std::endl;
	cout << endl;

	system("pause");
	return 0;
}