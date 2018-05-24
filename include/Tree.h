#pragma once
//=========================================================
//---------------------------------------------------------
#include<SDL\SDL.h>
#include<SDL_TTF\SDL_ttf.h>
#include"Prerequisities.h"
//---------------------------------------------------------
//=========================================================



//---------------------------------------------------------
struct Node
{
	//---------------------------------------------------------
	float data;
	unsigned short index;
	unsigned short rightChild;
	unsigned short leftChild;
	bool isNull;
	//---------------------------------------------------------

	//---------------------------------------------------------
	Node() : data(0), rightChild(0), leftChild(0), isNull(true) {}
	//---------------------------------------------------------

	//---------------------------------------------------------
	Node(float _data, unsigned short _index) : data(_data), index(_index), isNull(false)
	{
		rightChild = index * 2 + 2;
		leftChild = index * 2 + 1;
	}
	//---------------------------------------------------------

};
//---------------------------------------------------------

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

	Node& getLeftChild(int index);
	Node& getRightChild(int index);

	int getHeight() const;

	int getItemsCount() const { return m_items; }
	//--------------------------------------------

	//drawing functions.
	void draw(SDL_Renderer * renderer, TTF_Font *font);
	//-------------------------------------------------------------------------------

protected:

	//drawing functions.
	void drawCircle(SDL_Renderer * renderer, int centerX, int centerY, int radius);
	void renderText(
		SDL_Renderer *renderer,
		int x,
		int y,
		const char *text,
		TTF_Font *font,
		SDL_Color *color);
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
	//---------------------------------------------------------

private:

	Node * m_nodeArray;

	//size of array
	unsigned short m_size;

	//current items
	unsigned short m_items;
};
//---------------------------------------------------------
