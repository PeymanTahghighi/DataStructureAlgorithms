//============================================================================
//============================================================================
#include<Tree\BST.h>
//============================================================================
//============================================================================

//----------------------------------------------------------------------------
BST::BST(float _rootData)
{
	m_nodeArray[0].data = _rootData;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
BST::~BST()
{
	if (m_nodeArray)
	{
		delete[] m_nodeArray;
		m_nodeArray = nullptr;
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
void BST::add(float _data)
{
	int newNodeIndex = -1;
	//if we have any unassigned block in our array
	if (holes.size() != 0)
	{
		newNodeIndex = holes[holes.size()-1];
		holes.pop_back();
	}
	//we ran out of unassigned blocks
	else
	{
		checkSize();
		newNodeIndex = ++m_lastNodeIndex;
	}

	int index = 0;
	int indexInNodes = 0;
	int newHeight = 0;
	while (true)
	{
		if (m_nodeArray[index].data > _data)
		{
			indexInNodes = indexInNodes * 2 + 1;
			if (m_nodeArray[index].leftChild == 0)
			{
				Node node(_data, newNodeIndex, m_nodeArray[index].level + 1);
				m_nodeArray[newNodeIndex] = node;
				m_nodeArray[index].leftChild = newNodeIndex;
				m_nodeArray[newNodeIndex].father = index;
				//update total levels
				if (m_nodeArray[index].level + 1 > m_totalLevels)
					m_totalLevels = m_nodeArray[index].level + 1;
				
				break;
			}
			else if((m_nodeArray[index].leftChild != 0 && m_nodeArray[m_nodeArray[index].leftChild].isNull))
			{
				Node node(_data, m_nodeArray[index].leftChild, m_nodeArray[index].level + 1);
				m_nodeArray[m_nodeArray[index].leftChild] = node;
				m_nodeArray[m_nodeArray[index].leftChild].father = index;
				//update total levels
				if (m_nodeArray[index].level + 1 > m_totalLevels)
					m_totalLevels = m_nodeArray[index].level + 1;
				break;
			}
			else
			{
				index = m_nodeArray[index].leftChild;
			}

			newHeight++;
		}
		else
		{
			indexInNodes = indexInNodes * 2 + 2;
			if (m_nodeArray[index].rightChild == 0)
			{
				Node node(_data, newNodeIndex, m_nodeArray[index].level +1);
				m_nodeArray[newNodeIndex] = node;
				m_nodeArray[index].rightChild = newNodeIndex;
				m_nodeArray[newNodeIndex].father = index;
				//update total levels
				if (m_nodeArray[index].level + 1 > m_totalLevels)
					m_totalLevels = m_nodeArray[index].level + 1;
				break;
			}
			else if ((m_nodeArray[index].rightChild != 0 && m_nodeArray[m_nodeArray[index].rightChild].isNull))
			{
				Node node(_data, m_nodeArray[index].rightChild, m_nodeArray[index].level + 1);
				m_nodeArray[m_nodeArray[index].rightChild] = node;
				m_nodeArray[m_nodeArray[index].rightChild].father = index;
				//update total levels
				if (m_nodeArray[index].level + 1 > m_totalLevels)
					m_totalLevels = m_nodeArray[index].level + 1;
				break;
			}
			else
			{
				index = m_nodeArray[index].rightChild;
			}

			newHeight++;
		}

	}
	m_items++;
	m_height = newHeight;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
void BST::deleteNode(uint32_t index)
{
	//if our node contains no child
	if (!isLeftChildExist(index) && !isRightChildExist(index))
	{
		holes.push_back(index);
		m_nodeArray[index].isNull = true;
	}
	//if our node contains only left child
	else if (isLeftChildExist(index) && !isRightChildExist(index))
	{
		//if this node is left child of father.
		if (m_nodeArray[m_nodeArray[index].father].leftChild == index)
		{
			m_nodeArray[m_nodeArray[index].father].leftChild = m_nodeArray[index].leftChild;
			m_nodeArray[index].isNull = true;
			holes.push_back(index);
		}
		//if this node is right child of father
		else if(m_nodeArray[m_nodeArray[index].father].rightChild == index)
		{
			m_nodeArray[m_nodeArray[index].father].rightChild = m_nodeArray[index].leftChild;
			m_nodeArray[index].isNull = true;
			holes.push_back(index);
		}
		else
		{
			assert(1 == 0);
		}
	}
	//if our node contains only right child
	else if (!isLeftChildExist(index) && isRightChildExist(index))
	{
		//if this node is left child of father.
		if (m_nodeArray[m_nodeArray[index].father].leftChild == index)
		{
			m_nodeArray[m_nodeArray[index].father].leftChild = m_nodeArray[index].rightChild;
			m_nodeArray[index].isNull = true;
			holes.push_back(index);
		}
		//if this node is right child of father
		else if (m_nodeArray[m_nodeArray[index].father].rightChild == index)
		{
			m_nodeArray[m_nodeArray[index].father].rightChild = m_nodeArray[index].rightChild;
			m_nodeArray[index].isNull = true;
			holes.push_back(index);
		}
		//just in case of an error
		else
		{
			assert(1 == 0);
		}
	}
	//if our node contains both left and right childs
	else
	{
		uint32_t predIndex = getSuccessor(index);
		if (isLeftChildExist(predIndex))
		{
			if (m_nodeArray[m_nodeArray[predIndex].father].leftChild == predIndex)
			{
				m_nodeArray[m_nodeArray[predIndex].father].leftChild = m_nodeArray[predIndex].leftChild;
			}
			else if (m_nodeArray[m_nodeArray[predIndex].father].rightChild == predIndex)
			{
				m_nodeArray[m_nodeArray[predIndex].father].rightChild = m_nodeArray[predIndex].leftChild;
			}
			else
			{
				assert(1 == 0);
			}
		}
		else if (isRightChildExist(predIndex))
		{
			if (m_nodeArray[m_nodeArray[predIndex].father].leftChild == predIndex)
			{
				m_nodeArray[m_nodeArray[predIndex].father].leftChild = m_nodeArray[predIndex].rightChild;
			}
			else if (m_nodeArray[m_nodeArray[predIndex].father].rightChild == predIndex)
			{
				m_nodeArray[m_nodeArray[predIndex].father].rightChild = m_nodeArray[predIndex].rightChild;
			}
			else
			{
				assert(1 == 0);
			}
		}
		m_nodeArray[index].data = m_nodeArray[predIndex].data;
		m_nodeArray[predIndex].isNull = true;
		holes.push_back(predIndex);
	}

	m_items--;

}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
bool BST::isLeftChildExist(uint32_t index) const
{
	if (m_nodeArray[index].leftChild != 0)
	{
		if (!m_nodeArray[m_nodeArray[index].leftChild].isNull)
			return true;
	}
	return false;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
bool BST::isRightChildExist(uint32_t index) const
{
	if (m_nodeArray[index].rightChild != 0)
	{
		if (!m_nodeArray[m_nodeArray[index].rightChild].isNull)
			return true;
	}
	return false;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
int BST::getPredecessor(uint32_t index) const
{
	if (isLeftChildExist(index))
	{
		int newindex = m_nodeArray[index].leftChild;
		while (true)
		{
			if (isRightChildExist(newindex))
			{
				newindex = m_nodeArray[newindex].rightChild;
			}
			else
			{
				return newindex;
			}
		}
	}
	else
	{
		uint32_t fatherIndex = m_nodeArray[index].father;
		uint32_t newIndex = index;
		while (true)
		{
			if (m_nodeArray[fatherIndex].rightChild == newIndex)
				return fatherIndex;
			else
			{
				newIndex = fatherIndex;
				fatherIndex = m_nodeArray[fatherIndex].father;
			}
		}
	}


}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
int BST::getSuccessor(uint32_t index) const
{
	if (isRightChildExist(index))
	{
		int newindex = m_nodeArray[index].rightChild;
		while (true)
		{
			if (isLeftChildExist(newindex))
				newindex = m_nodeArray[newindex].leftChild;
			else
			{
				return newindex;
				break;
			}
		}
	}
	else
	{
		uint32_t fatherIndex = m_nodeArray[index].father;
		uint32_t newIndex = index;
		while (true)
		{
			if (m_nodeArray[fatherIndex].leftChild == newIndex)
				return fatherIndex;
			else
			{
				newIndex = fatherIndex;
				fatherIndex = m_nodeArray[fatherIndex].father;
			}
		}
	}
}
//----------------------------------------------------------------------------