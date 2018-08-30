//===============================================================================
//===============================================================================
#include<iostream>
#include<time.h>
#include"Tree/BST.h"
#include<algorithm>
//===============================================================================
//===============================================================================

//-------------------------------------------------------------------------------
int main(int /*argc*/, char * /*argv*/[])
{
	//enable memory leak checks.
#if defined(_DEBUG) | (DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	//------------------------------------------
	BST *tree  = new BST(15);
	int arraySize = 0;
	std::cout << "Enter array size : ";
	std::cin >> arraySize;
	getchar();

	srand((unsigned int)time(nullptr));

	tree->add(10);
	tree->add(5);
	tree->add(30);
	tree->add(40);
	tree->add(17);
	tree->add(25);
	tree->add(20);

	//sort array by traversing inorder.
	tree->traverseInOrder(0);


	/*Node no = tree->getNode(5);
	std::cout << "\n\nNode 2 is : " << no.data << "\n";
	int i = tree->getPredecessor(5);
	Node n =  tree->getNode(i);
	std::cout << "===========\n\n";
	std::cout << n.data;*/
	std::cout << "\n\n------------\n\n";

	tree->deleteNode(0);
	tree->traverseInOrder(0);


	std::cout << "\n\n------------\n\n";

	tree->deleteNode(0);
	tree->traverseInOrder(0);

	std::cout << "\n\n------------\n\n";

	tree->deleteNode(0);
	tree->traverseInOrder(0);

	//tree->deleteNode(0);
	//tree->traverseInOrder(0);

	tree->printHoles();

	getchar();

	//cleanup
	delete tree;
	//--------------------------

	//dump memory leaks
	_CrtDumpMemoryLeaks();

	return 0;
}
//-------------------------------------------------------------------------------
