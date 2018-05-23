#pragma once
//=========================================================
//---------------------------------------------------------
#include<SDL\SDL.h>
//---------------------------------------------------------
//=========================================================



////---------------------------------------------------------
//struct Node
//{
//	//---------------------------------------------------------
//	float data;
//	Node * left, *right;
//	int depth;
//	//---------------------------------------------------------
//
//	//used for drawing and no more usage,
//	//remove for basic tree implementation and not visualization.
//	int centerX;
//	int centerY;
//	//---------------------------------------------------------
//
//	//---------------------------------------------------------
//	Node(float _data) : data(_data), left(nullptr), right(nullptr), centerX(0.0f), centerY(0.0f), depth(0) { }
//	//---------------------------------------------------------
//
//	//---------------------------------------------------------
//	Node(float _data, Node * _left, Node * _right) : data(_data), right(_right), left(_left), centerX(0.0f), centerY(0.0f), depth(0) { }
//	//---------------------------------------------------------
//
//};
////---------------------------------------------------------

//---------------------------------------------------------
class Tree
{
public:

	//Constructors
	Tree(float _rootData);
	//---------------------------------------------------------

	//Destructors
	~Tree();
	//---------------------------------------------------------

	//Functionality
	virtual void add(float _data);

	void traverseInOrder(int index);
	void traversePostOrder(int index);
	void traversePreOrder(int index);

	bool isLeftChildExist(int index);
	bool isRightChildExist(int index);

	int getLeftChild(int index);
	int getRightChild(int index);

	void draw(SDL_Renderer * renderer);
	//---------------------------------------------------------

protected:

	//---------------------------------------------------------
	void drawCircle(SDL_Renderer * renderer, int centerX, int centerY, int radius);
	//---------------------------------------------------------

	/*
	check size and if array is full create
	an array double the size of current array
	and add all items to it.
	*/
	void checkSize();
	//---------------------------------------------------------

private:

	//---------------------------------------------------------
	void addToEmptyPlace(float data);

private:

	float * m_array;

	//size of array
	int m_size;

	//current items
	int m_items;

	int m_height;
};
//---------------------------------------------------------
