#pragma once
//============================================================================
//============================================================================
#include<SDL\SDL.h>
#include<SDL_TTF\SDL_ttf.h>
#include"Tree\Tree.h"
//============================================================================
//============================================================================

//----------------------------------------------------------------------------
class BST : public Tree
{
public:
	
	//Constructors
	BST(float _rootData);
	//-------------------------------------------

	//Functionality
	virtual void add(float _data) override;

	virtual int getHeight() const override { return m_height; }
	//--------------------------------------------

private:

};
//----------------------------------------------------------------------------