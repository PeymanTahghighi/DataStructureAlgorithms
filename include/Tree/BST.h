#pragma once
//============================================================================
//============================================================================
#include<SDL\SDL.h>
#include<SDL_TTF\SDL_ttf.h>
#include"Tree\Tree.h"
#include<vector>
//============================================================================
//============================================================================

//----------------------------------------------------------------------------
class BST : public Tree
{
public:
	
	//Constructors
	BST(float _rootData);
	//-------------------------------------------

	//Destructors
	~BST();
	//-------------------------------------------

	//Functionality
	virtual void add(float _data) override;
	virtual void deleteNode(uint32_t index);

	virtual int getHeight() const override { return m_height; }

	virtual bool isLeftChildExist(uint32_t index) const override;
	virtual bool isRightChildExist(uint32_t index) const override;

	int getPredecessor(uint32_t index) const;
	int getSuccessor(uint32_t index) const;

	//--------------------------------------------

private:
	std::vector<int> holes;
};
//----------------------------------------------------------------------------
