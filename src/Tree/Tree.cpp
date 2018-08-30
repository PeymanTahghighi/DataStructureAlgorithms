//=======================================================================================
//=======================================================================================
#include "Tree\Tree.h"
#include<iostream>
#include<vector>
#include<stdlib.h>
//=======================================================================================
//=======================================================================================

//---------------------------------------------------------------------------------------
Tree::Tree(float _rootData)
{
	m_nodeArray = new Node[1];
	Node node(_rootData, 0, 0);
	m_nodeArray[0] = node;
	m_size = 1;
	m_items = 1;
	m_height = 0;
	m_lastNodeIndex = 0;
	m_totalLevels = 0;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
Tree::Tree()
{
	m_nodeArray = new Node[1];
	Node node(0, 0, 0);
	m_nodeArray[0] = node;
	m_size = 1;
	m_items = 1;
	m_lastNodeIndex = 0;
	m_totalLevels = 0;

#if ENABLE_DRAWING_FUNCTIONS
	m_maxIndex = 0;
#endif

}

//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
Tree::~Tree()
{
	if (m_nodeArray)
	{
		delete[] m_nodeArray;
		m_nodeArray = nullptr;
	}
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
void Tree::add(float _data)
{
	checkSize();
	Node node(_data, m_items, 0);
	m_nodeArray[m_items] = node;

	m_items++;

	for (uint32_t i = 0; i < m_items; ++i)
	{
		if (i * 2 + 1 < m_items)
		{
			m_nodeArray[i].leftChild = i * 2 + 1;
		}
		if (i * 2 + 2 < m_items)
		{
			m_nodeArray[i].rightChild = i * 2 + 2;
		}
	}
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
void Tree::checkSize()
{
	if (m_size == m_items)
	{
		grow();
	}
}
//---------------------------------------------------------------------------------------

#if ENABLE_DRAWING_FUNCTIONS
//drawing functions
//====================================================================================================
//---------------------------------------------------------------------------------------
void Tree::draw(SDL_Renderer *renderer, TTF_Font *font)
{
	int startX = SCREEN_WIDTH / 2;
	int startY = 50;
	int radius = 20;
	
	resizeWidths(0);
	drawNode(renderer, font, 0, startX, startY, radius, 0);
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
void Tree::drawNode(SDL_Renderer * renderer,
	TTF_Font * font,
	int index, int x, int y, int radius
	, int side)
{

	if (side == -1)
	{
		x -= m_nodeArray[index].rightWidth;
	}
	else if (side == 1)
	{
		x += m_nodeArray[index].leftWidth;
	}

	drawCircle(renderer, x, y, radius);
	std::string dataString;
	intToString((int)m_nodeArray[index].data, dataString);
	SDL_Color color;
	color.r = 200;
	color.g = 0;
	color.b = 100;
	color.a = 255;
	renderText(renderer, x, y, dataString.c_str(), font, &color);

	//if left child exist for this node
	if (m_nodeArray[index].leftChild != 0 && !m_nodeArray[m_nodeArray[index].rightChild].isNull)
	{
		SDL_RenderDrawLine(renderer, x, y + radius, x - m_nodeArray[m_nodeArray[index].leftChild].rightWidth, y + DRAW_Y_OFFSET - radius);
		drawNode(renderer, font, m_nodeArray[index].leftChild, x, y + DRAW_Y_OFFSET, radius, -1);
	}
	//if right child exist for this node
	if (m_nodeArray[index].rightChild != 0 && !m_nodeArray[m_nodeArray[index].rightChild].isNull)
	{
		SDL_RenderDrawLine(renderer, x, y + radius, x + m_nodeArray[m_nodeArray[index].rightChild].leftWidth, y + DRAW_Y_OFFSET - radius);
		drawNode(renderer, font, m_nodeArray[index].rightChild, x, y + DRAW_Y_OFFSET, radius, 1);
	}
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
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
	rect.x = x - surface->w / 2;
	rect.y = y - surface->h / 2;
	rect.w = surface->w;
	rect.h = surface->h;
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);

}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
int Tree::resizeWidths(uint32_t index)
{
	if (m_nodeArray[index].leftChild != 0 && !m_nodeArray[m_nodeArray[index].rightChild].isNull)
	{
		m_nodeArray[index].leftWidth = Max<uint32_t>(resizeWidths(m_nodeArray[index].leftChild), 25);
	}
	else
	{
		m_nodeArray[index].leftWidth = 25;
	}
	//if right child exist for this node
	if (m_nodeArray[index].rightChild != 0 && !m_nodeArray[m_nodeArray[index].rightChild].isNull)
	{
		m_nodeArray[index].rightWidth = Max<uint32_t>(resizeWidths(m_nodeArray[index].rightChild), 25);
	}
	else
	{
		m_nodeArray[index].rightWidth = 25;
	}

	return m_nodeArray[index].leftWidth + m_nodeArray[index].rightWidth;

}
//---------------------------------------------------------------------------------------
//====================================================================================================
#endif

//---------------------------------------------------------------------------------------
void Tree::traverseInOrder(uint32_t index)
{
	if (isLeftChildExist(index))
		traverseInOrder(m_nodeArray[index].leftChild);
	std::cout << m_nodeArray[index].data << "\n";
	if (isRightChildExist(index))
		traverseInOrder(m_nodeArray[index].rightChild);
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
void Tree::traversePostOrder(uint32_t index)
{
	if (isLeftChildExist(index))
		traversePostOrder(m_nodeArray[index].leftChild);
	if (isRightChildExist(index))
		traversePostOrder(m_nodeArray[index].rightChild);
	std::cout << m_nodeArray[index].data << "\n";
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
void Tree::traversePreOrder(uint32_t index)
{
	std::cout << m_nodeArray[index].data << "\n";
	if (isLeftChildExist(index))
		traversePreOrder(m_nodeArray[index].leftChild);
	if (isRightChildExist(index))
		traversePreOrder(m_nodeArray[index].rightChild);
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
Node& Tree::getLeftChild(uint32_t index)
{
	return m_nodeArray[m_nodeArray[index].leftChild];
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
Node& Tree::getRightChild(uint32_t index)
{
	return m_nodeArray[m_nodeArray[index].rightChild];
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
bool Tree::isLeftChildExist(uint32_t index) const
{
	if (m_nodeArray[index].leftChild < m_size)
	{
		if (!m_nodeArray[m_nodeArray[index].leftChild].isNull)
			return true;
	}
	return false;
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
bool Tree::isRightChildExist(uint32_t index) const
{
	if (m_nodeArray[index].rightChild < m_size)
	{
		if (!m_nodeArray[m_nodeArray[index].rightChild].isNull)
			return true;
	}
	return false;
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
int Tree::getHeight() const
{
	return (int)floorf(log2f((float)m_items));
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
void Tree::grow()
{
	std::cout << "Grow size from \"" << m_size << "\"";
	Node * tmp = new Node[m_size * 2];
	for (uint32_t i = 0; i < m_size; ++i)
	{
		tmp[i] = m_nodeArray[i];
	}

	delete[] m_nodeArray;
	m_nodeArray = tmp;
	m_size *= 2;

	std::cout << " to \"" << m_size << "\"\n\n";

}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
void Tree::printHoles()
{
	std::cout << "\n*============Start printing holes=================*\n";
	int totalHoles = 0;
	for (unsigned int i = 0; i < m_size; ++i)
	{
		if (m_nodeArray[i].isNull == true)
		{
			totalHoles++;
			std::cout << "\nHole in : " << i;
		}
	}
	std::cout << "\nTotal Holes : " << totalHoles;
	std::cout << "\n*============End printing holes===================*\n";
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
void Tree::getNodesInLevel(uint32_t level, std::vector<int> &ret)
{
	assert(level <= m_totalLevels);
	for (unsigned int i = 0; i < m_size; ++i)
	{
		if (!m_nodeArray[i].isNull && m_nodeArray[i].level == level)
			ret.push_back(i);
	}
}
//---------------------------------------------------------------------------------------
