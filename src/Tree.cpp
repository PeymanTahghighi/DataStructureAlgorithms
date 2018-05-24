//==========================================================================
//--------------------------------------------------------------------------
#include "Tree.h"
#include<iostream>
#include<vector>
#include<stdlib.h>
//--------------------------------------------------------------------------
//==========================================================================

//--------------------------------------------------------------------------
Tree::Tree(float _rootData)
{
	m_nodeArray = new Node[1];
	Node node(_rootData, 0);
	m_nodeArray[0] = node;
	m_size = 1;
	m_items = 1;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
Tree::~Tree()
{
	delete[] m_nodeArray;
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
	Node node(_data, m_items);
	m_nodeArray[m_items] = node;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void Tree::checkSize()
{
	if (m_size == m_items)
	{
		Node * tmp = new Node[m_size * 2];
		for (int i = 0; i < m_size; ++i)
		{
			tmp[i] = m_nodeArray[i];
		}

		delete[] m_nodeArray;
		m_nodeArray = tmp;
		m_size *= 2;
	}
}
//--------------------------------------------------------------------------

//drawing functions
//====================================================================================================
//--------------------------------------------------------------------------
void Tree::draw(SDL_Renderer *renderer, TTF_Font *font)
{
	int radius = 20;
	int yOffset = 75;
	int xOffset = 0;
	int x = 1800 / 2;
	int xEnd = x;
	int xStart = x;
	SDL_Color color;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 255;

	//calculate x offset
	//calculate offset that all nods in last
	//level fit correctly.
	int totalHeight = (int)floorf(log2f(m_items));
	int nodeInLastLevel = (int)pow(2, (int)totalHeight);
	//start to end in last level.
	int totalXInLastLevel = nodeInLastLevel * radius;

	//we get xOffset from this equation->  totalXInLastLevel = (xEnd + xOffset*totalHeight) - (xStart - xOffset*totalHeight)
	xOffset = (totalXInLastLevel - xEnd + xStart) / totalHeight;
	//---------------------

	//each node father x.
	std::vector<int> allNodeX;

	std::string numberString;

	for (int i = 0; i < m_items; ++i)
	{
		if (m_nodeArray[i].isNull)
			continue;

		int j = i + 1;
		int height = (int)floorf(log2f((float)j));
		//we add and offset to each node.
		int y = yOffset*height + radius;

		int numInLevel = (j) % (int)pow(2, height);

		//X offset per node.
		int xPerNode = (int)((xEnd - xStart) / (pow(2, height) - 1));

		//calculate this node x positon using its index in level and offset.
		x = numInLevel*xPerNode;
		x += xStart;

		allNodeX.push_back(x);

		//draw circle and data
		floatToString(m_nodeArray[i].data, numberString);
		drawCircle(renderer, x, y, radius);
		renderText(renderer, x, y, numberString.c_str(), font, &color);
		//---------------------------------------------------

		//draw line to father if exits
		int fatherIndex = (int)floorf((int)j / 2.0f);
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
		y = (int)sqrt(radiusPow2 - x*x);
	}
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void Tree::renderText(
	SDL_Renderer *renderer,
	int x,
	int y,
	const char *text,
	TTF_Font *font,
	SDL_Color *color)
{
	SDL_Rect rect;
	SDL_Surface *surface;
	SDL_Texture *texture;

	surface = TTF_RenderText_Solid(font, text, *color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	rect.x = x - surface->w/2;
	rect.y = y - surface->h/2;
	rect.w = surface->w;
	rect.h = surface->h;
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}
//--------------------------------------------------------------------------
//====================================================================================================

//--------------------------------------------------------------------------
void Tree::traverseInOrder(int index)
{
	if (isLeftChildExist(index))
		traverseInOrder(m_nodeArray[index].leftChild);
	std::cout << m_nodeArray[index].data << "\n";
	if (isRightChildExist(index))
		traverseInOrder(m_nodeArray[index].rightChild);
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void Tree::traversePostOrder(int index)
{
	if (isLeftChildExist(index))
		traversePostOrder(m_nodeArray[index].leftChild);
	if (isRightChildExist(index))
		traversePostOrder(m_nodeArray[index].rightChild);
	std::cout << m_nodeArray[index].data << "\n";
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void Tree::traversePreOrder(int index)
{
	std::cout << m_nodeArray[index].data << "\n";
	if (isLeftChildExist(index))
		traversePreOrder(m_nodeArray[index].leftChild);
	if (isRightChildExist(index))
		traversePreOrder(m_nodeArray[index].rightChild);
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
Node& Tree::getLeftChild(int index)
{
	return m_nodeArray[m_nodeArray[index].leftChild];
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
Node& Tree::getRightChild(int index)
{
	return m_nodeArray[m_nodeArray[index].rightChild];
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
bool Tree::isLeftChildExist(int index)
{
	if (m_nodeArray[index].leftChild < m_items)
	{
		if (!m_nodeArray[m_nodeArray[index].leftChild].isNull)
			return true;
	}
	return false;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
bool Tree::isRightChildExist(int index)
{
	if (m_nodeArray[index].rightChild < m_items)
	{
		if (!m_nodeArray[m_nodeArray[index].rightChild].isNull)
			return true;
	}
	return false;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
int Tree::getHeight() const
{
	return (int)floorf(log2f(m_items));
}
//--------------------------------------------------------------------------
