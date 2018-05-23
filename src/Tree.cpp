//==========================================================================
//--------------------------------------------------------------------------
#include "Tree.h"
#include<queue>
#include<iostream>
#include<vector>
//--------------------------------------------------------------------------
//==========================================================================


//--------------------------------------------------------------------------
Tree::Tree(float _rootData)
{
	m_array = new float[1];
	m_array[0] = _rootData;
	m_size = 1;
	m_items = 1;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
Tree::~Tree()
{
	delete[] m_array;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void Tree::add(float _data)
{
	checkSize();
	addToEmptyPlace(_data);
	m_items++;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void Tree::addToEmptyPlace(float _data)
{
	m_array[m_items] = _data;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void Tree::draw(SDL_Renderer *renderer)
{
	int radius = 10;
	int yOffset = 50;
	int xOffset = 0;
	int x = 800 / 2;
	int xEnd = 800 / 2;
	int xStart = 800 / 2;

	//calculate x offset
	//calculate offset that all nods in last
	//level fit correctly.
	int totalHeight = floorf(log2f(m_items));
	int nodeInLastLevel = pow(2, totalHeight);
	//start to end in last level.
	int totalXInLastLevel = nodeInLastLevel * radius;

	//we get xOffset from this equation->  totalXInLastLevel = (xEnd + xOffset*totalHeight) - (xStart - xOffset*totalHeight)
	xOffset = (totalXInLastLevel - xEnd + xStart) / totalHeight;

	//---------------------

	//each node father x.
	std::vector<int> allNodeX;

	for (int i = 0; i < m_items; ++i)
	{

		int j = i + 1;
		int height = floorf(log2(j));
		//we add and offset to each node.
		int y = yOffset*height + 20;

		int numInLevel = (j) % (int)pow(2, height);

		//X offset per node.
		int xPerNode = (xEnd - xStart) / (pow(2, height) - 1);

		//calculate this node x positon using its index in level and offset.
		x = numInLevel*xPerNode;
		x += xStart;

		allNodeX.push_back(x);

		drawCircle(renderer, x, y, radius);

		//draw line to father if exits
		int fatherIndex = floorf(j / 2);
		if (fatherIndex != 0)
		{
			int fatherX = allNodeX.at(fatherIndex - 1);
			int fatherY = y - yOffset;
			SDL_RenderDrawLine(renderer, x, y - radius, fatherX, fatherY + radius);
		}
		//-------------------------------

		//if we reach this level end.
		if (j == pow(2, height + 1) - 1)
		{
			//calculate next level start and end X.
			xEnd = xEnd + xOffset;
			xStart = xStart - xOffset;;
		}
		//------------------------------------
	}

	allNodeX.clear();
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void Tree::checkSize()
{
	if (m_size == m_items)
	{
		float * tmp = new float[m_size * 2];
		for (int i = 0; i < m_size; ++i)
		{
			tmp[i] = m_array[i];
		}

		delete[] m_array;
		m_array = tmp;
		m_size *= 2;
	}
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void Tree::drawCircle(SDL_Renderer * renderer, int centerX, int centerY, int radius)
{
	int step = 1;
	int x = 0;
	int y = radius;
	int radiusPow2 = radius*radius;
	while (x <= y)
	{

		SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
		SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
		SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
		SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);

		SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
		SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);
		SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
		SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);

		x += step;
		y = sqrt(radiusPow2 - x*x);
	}
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void Tree::traverseInOrder(int index)
{
	if (isLeftChildExist(index))
		traverseInOrder(getLeftChild(index));
	std::cout << m_array[index] << "\n";
	if (isRightChildExist(index))
		traverseInOrder(getRightChild(index));
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void Tree::traversePostOrder(int index)
{
	if (isLeftChildExist(index))
		traversePostOrder(getLeftChild(index));
	if (isRightChildExist(index))
		traversePostOrder(getRightChild(index));
	std::cout << m_array[index] << "\n";
}
//--------------------------------------------------------------------------

void Tree::traversePreOrder(int index)
{
	std::cout << m_array[index] << "\n";
	if (isLeftChildExist(index))
		traversePreOrder(getLeftChild(index));
	if (isRightChildExist(index))
		traversePreOrder(getRightChild(index));
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
bool Tree::isLeftChildExist(int index)
{
	if ((index * 2) + 1 >= m_items)
		return false;
	return true;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
bool Tree::isRightChildExist(int index)
{
	if ((index * 2) + 2 >= m_items)
		return false;
	return true;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
int Tree::getLeftChild(int index)
{
	return index * 2 + 1;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
int Tree::getRightChild(int index)
{
	return index * 2 + 2;
}
//--------------------------------------------------------------------------