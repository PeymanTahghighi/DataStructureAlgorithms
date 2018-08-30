#pragma once
//=========================================================
//---------------------------------------------------------
#include"Prerequisities.h"

#if ENABLE_DRAWING_FUNCTIONS
#include<SDL\SDL.h>
#include<SDL_TTF\SDL_ttf.h>
#endif

//---------------------------------------------------------
//=========================================================

//---------------------------------------------------------
struct Node
{
	//---------------------------------------------------------
	float data;
	uint32_t rightChild;
	uint32_t leftChild;
	bool isNull;
	uint32_t father;
	uint32_t index;
	uint32_t level;
	uint32_t leftWidth;
	uint32_t rightWidth;

	//---------------------------------------------------------

	//---------------------------------------------------------
	Node() : data(0), 
		rightChild(0), 
		leftChild(0), 
		isNull(true),
		leftWidth(25),
		rightWidth(25)
	{}
	//---------------------------------------------------------

	//---------------------------------------------------------
	Node(float _data, uint32_t _index,uint32_t _level) : 
		data(_data),
		isNull(false),
		father(0),
		rightChild(0),
		leftChild(0),
		index(_index),
		level(_level),
		leftWidth(25),
		rightWidth(25)
	{

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
	Tree();
	//---------------------------------------------------------

	//Destructors
	~Tree();
	//---------------------------------------------------------

	//Functionality
	virtual void add(float _data);

	virtual void traverseInOrder(uint32_t index);
	virtual void traversePostOrder(uint32_t index);
	virtual void traversePreOrder(uint32_t index);

	virtual bool isLeftChildExist(uint32_t index) const;
	virtual bool isRightChildExist(uint32_t index) const;

	virtual Node& getLeftChild(uint32_t index);
	virtual Node& getRightChild(uint32_t index);

	const Node & getNode(unsigned int index) const { assert(index < m_items); return m_nodeArray[index]; }

	void printHoles();

	virtual int getHeight() const;

	int getItemsCount() const { return m_items; }

	void getNodesInLevel(uint32_t level, std::vector<int> &ret);

	//--------------------------------------------

#if ENABLE_DRAWING_FUNCTIONS
	//drawing functions.
	void draw(SDL_Renderer * renderer, TTF_Font *font);
	//-------------------------------------------------------------------------------
#endif

protected:

#if ENABLE_DRAWING_FUNCTIONS
	//drawing functions.
	void drawCircle(SDL_Renderer * renderer, int centerX, int centerY, int radius);
	void drawNode(SDL_Renderer * renderer,TTF_Font * font,int index, int x, int y, int radius,int side);
	void renderText(
		SDL_Renderer *renderer,
		int x,
		int y,
		const char *text,
		TTF_Font *font,
		SDL_Color *color);
	//---------------------------------------------------------
#endif

	/*
	check size and if array is full create
	an array double the size of current array
	and add all items to it.
	*/
	void checkSize();
	//---------------------------------------------------------

	void grow();
	//---------------------------------------------------------

	int resizeWidths(uint32_t index);
	//---------------------------------------------------------

protected:

	Node * m_nodeArray;

	//size of array
	uint32_t m_size;

	//current items
	uint32_t m_items;

	//index of last node in array
	uint32_t m_lastNodeIndex;

	uint32_t m_height;

	uint32_t m_totalLevels;

#if ENABLE_DRAWING_FUNCTIONS
	//save maximum index in tree.
	//note that we use this function only for drawing.
	uint32_t m_maxIndex;
#endif

};
//---------------------------------------------------------
