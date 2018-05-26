//============================================================================
//============================================================================
#include<Tree\BST.h>
//============================================================================
//============================================================================

//----------------------------------------------------------------------------
BST::BST(float _rootData)
{
	m_nodeArray = new Node[1];
	Node node(_rootData, 0);
	m_nodeArray[0] = node;
	m_items = 1;
	m_size = 1;
	m_height = 0;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
void BST::add(float _data)
{
	checkSize();
	int index = 0;
	while (true)
	{
		if (m_nodeArray[index].data > _data)
		{
			if (m_nodeArray[index].leftChild < m_size)
			{
				if (m_nodeArray[m_nodeArray[index].leftChild].isNull)
				{
					Node node(_data, m_nodeArray[index].leftChild);
					m_nodeArray[m_nodeArray[index].leftChild] = node;
					m_height = Max<int>((int)log2(m_nodeArray[index].leftChild), m_height);
					break;
				}
				else
				{
					index = m_nodeArray[index].leftChild;
				}
			}
			else
			{
				grow();
				continue;
			}
		}
		else
		{
			if (m_nodeArray[index].rightChild < m_size)
			{
				if (m_nodeArray[m_nodeArray[index].rightChild].isNull)
				{
					Node node(_data, m_nodeArray[index].rightChild);
					m_nodeArray[m_nodeArray[index].rightChild] = node;
					m_height = Max<int>((int)log2(m_nodeArray[index].rightChild), m_height);
					break;
				}
				else
				{
					index = m_nodeArray[index].rightChild;
				}
			}
			else
			{
				grow();
				continue;
			}
		}
	}
	m_items++;
}
//----------------------------------------------------------------------------

