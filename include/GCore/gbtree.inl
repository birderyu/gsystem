#ifndef _CORE_B_TREE_INLINE_
#define _CORE_B_TREE_INLINE_

#define G_BTREE_TEMPLATE	template<typename KeyT, typename ValueT, gsize M, gsize KEY_MAX, gsize KEY_MIN, gsize CHILD_MAX, gsize CHILD_MIN, typename NodeT>
#define G_BTREE_QUAL		GBTree<KeyT, ValueT, M, KEY_MAX, KEY_MIN, CHILD_MAX, CHILD_MIN, NodeT>

namespace gsystem {

G_BTREE_TEMPLATE GINLINE
G_BTREE_QUAL::GBTree()
{
	m_pRoot = GNULL;  //创建一棵空的B树  
}

G_BTREE_TEMPLATE GINLINE
G_BTREE_QUAL::~GBTree()
{
	Clear();
}

G_BTREE_TEMPLATE GINLINE
gbool G_BTREE_QUAL::Insert(const KeyT &key, const ValueT &value)
{
	// 检查该关键字是否已经存在
	if (Contains(key))
	{
		return false;
	}
	else
	{
		// 检查是否为空树
		if (m_pRoot == GNULL)
		{
			m_pRoot = new NodeT();
		}
		if (m_pRoot->m_nKeyNum == KEY_MAX) //检查根节点是否已满  
		{
			NodeT *pNode = new NodeT();  //创建新的根节点  
			pNode->m_bIsLeaf = false;
			pNode->m_pChild[0] = m_pRoot;
			SplitChild(pNode, 0, m_pRoot);
			m_pRoot = pNode;  //更新根节点指针  
		}
		InsertNonFull(m_pRoot, key, value);
		return true;
	}
}

G_BTREE_TEMPLATE GINLINE
gbool G_BTREE_QUAL::Delete(const KeyT &key)
{
	if (!Search(m_pRoot, key))  //不存在  
	{
		return false;
	}
	if (m_pRoot->m_nKeyNum == 1)//特殊情况处理  
	{
		if (m_pRoot->m_bIsLeaf)
		{
			Clear();
			return true;
		}
		else
		{
			NodeT *pChild1 = m_pRoot->m_pChild[0];
			NodeT *pChild2 = m_pRoot->m_pChild[1];
			if (pChild1->m_nKeyNum == KEY_MIN &&
				pChild2->m_nKeyNum == KEY_MIN)
			{
				MergeChild(m_pRoot, 0);
				DeleteNode(m_pRoot);
				m_pRoot = pChild1;
			}
		}
	}
	Recursive_remove(m_pRoot, key);
	return true;
}

G_BTREE_TEMPLATE GINLINE
gbool G_BTREE_QUAL::Contains(const KeyT &key) const
{
	return Search(m_pRoot, key);
}

G_BTREE_TEMPLATE GINLINE
gvoid G_BTREE_QUAL::Clear()
{
	Recursive_clear(m_pRoot);
	m_pRoot = NULL;
}

G_BTREE_TEMPLATE GINLINE
gvoid G_BTREE_QUAL::Recursive_clear(NodeT *pNode)
{
	if (pNode != GNULL)
	{
		if (!pNode->m_bIsLeaf)
		{
			for (gsize i = 0; i <= pNode->m_nKeyNum; ++i)
				Recursive_clear(pNode->m_pChild[i]);
		}
		DeleteNode(pNode);
	}
}

G_BTREE_TEMPLATE GINLINE
gvoid G_BTREE_QUAL::DeleteNode(NodeT *&pNode)
{
	if (pNode != GNULL)
	{
		delete pNode;
		pNode = GNULL;
	}
}

G_BTREE_TEMPLATE GINLINE
gbool G_BTREE_QUAL::Search(NodeT *pNode, const KeyT &key) const
{
	if (pNode == NULL)  //检测节点指针是否为空，或该节点是否为叶子节点  
	{
		return false;
	}
	
	gsize i;
	// 找到使key<=pNode->keyValue[i]成立的最小下标i  
	for (i = 0; i < pNode->m_nKeyNum && key > *(pNode->m_tKeys + i); ++i)
	{

	}
	if (i < pNode->m_nKeyNum && key == pNode->m_tKeys[i])
	{
		return true;
	}
	else
	{
		// 检查该节点是否为叶子节点
		if (pNode->m_bIsLeaf)
		{
			return false;
		}
		else
		{
			return Search(pNode->m_pChild[i], key);
		}
	}
}

G_BTREE_TEMPLATE GINLINE
gvoid G_BTREE_QUAL::SplitChild(NodeT *pParent, gint nChildIndex, NodeT *pChild)
{
	// 将pChild分裂成pLeftNode和pChild两个节点  
	NodeT *pRightNode = new NodeT();//分裂后的右节点  
	pRightNode->m_bIsLeaf = pChild->m_bIsLeaf;
	pRightNode->m_nKeyNum = KEY_MIN;
	for (gsize i = 0; i < KEY_MIN; ++i)//拷贝关键字的值  
	{
		pRightNode->m_tKeys[i] = pChild->m_tKeys[i + CHILD_MIN];
	}
	if (!pChild->m_bIsLeaf)  //如果不是叶子节点，拷贝孩子节点指针  
	{
		for (gsize i = 0; i < CHILD_MIN; ++i)
		{
			pRightNode->m_pChild[i] = pChild->m_pChild[i + CHILD_MIN];
		}
	}

	pChild->m_nKeyNum = KEY_MIN;  //更新左子树的关键字个数  

	for (gsize i = pParent->m_nKeyNum; i > nChildIndex; --i)//将父节点中的nChildIndex后的所有关键字的值和子树指针向后移一位  
	{
		pParent->m_pChild[i + 1] = pParent->m_pChild[i];
		pParent->m_tKeys[i] = pParent->m_tKeys[i - 1];
	}
	++pParent->m_nKeyNum;  //更新父节点的关键字个数  
	pParent->m_pChild[nChildIndex + 1] = pRightNode;  //存储右子树指针  
	pParent->m_tKeys[nChildIndex] = pChild->m_tKeys[KEY_MIN];//把节点的中间值提到父节点  
}

G_BTREE_TEMPLATE GINLINE
gvoid G_BTREE_QUAL::InsertNonFull(NodeT *pNode, const KeyT &key, const ValueT &value)
{
	gint i = pNode->m_nKeyNum;  //获取节点内关键字个数  
	if (pNode->m_bIsLeaf)      //pNode是叶子节点  
	{
		while (i > 0 && key < pNode->m_tKeys[i - 1])   //从后往前，查找关键字的插入位置  
		{
			pNode->m_tKeys[i] = pNode->m_tKeys[i - 1];  //向后移位  
			--i;
		}
		pNode->m_tKeys[i] = key;		//插入关键字的值  
		pNode->m_tValues[i] = value;	//插入关键字的值  
		++pNode->m_nKeyNum; //更新节点关键字的个数  
	}
	else//pNode是内节点  
	{
		while (i > 0 && key < pNode->m_tKeys[i - 1])   //从后往前，查找关键字的插入的子树  
			--i;
		NodeT *pChild = pNode->m_pChild[i];  //目标子树结点指针   
		if (pChild->m_nKeyNum == KEY_MAX)  //子树节点已满  
		{
			SplitChild(pNode, i, pChild);//分裂子树节点  
			if (key > pNode->m_tKeys[i])   //确定目标子树  
				pChild = pNode->m_pChild[i + 1];
		}
		InsertNonFull(pChild, key, value);  //插入关键字到目标子树节点  
	}
}

G_BTREE_TEMPLATE GINLINE
gvoid G_BTREE_QUAL::MergeChild(NodeT *pParent, gsize index)
{
	NodeT *pChild1 = pParent->m_pChild[index];
	NodeT *pChild2 = pParent->m_pChild[index + 1];
	// 将pChild2数据合并到pChild1  
	pChild1->m_nKeyNum = KEY_MAX;
	pChild1->m_tKeys[KEY_MIN] = pParent->m_tKeys[index]; // 将父节点index的值下移  
	for (gsize i = 0; i < KEY_MIN; ++i)
	{
		pChild1->m_tKeys[i + KEY_MIN + 1] = pChild2->m_tKeys[i];
	}
	if (!pChild1->m_bIsLeaf)
	{
		for (gsize i = 0; i < CHILD_MIN; ++i)
		{
			pChild1->m_pChild[i + CHILD_MIN] = pChild2->m_pChild[i];
		}
	}

	//父节点删除index的key，index后的往前移一位  
	--pParent->m_nKeyNum;
	for (gsize i = index; i < pParent->m_nKeyNum; ++i)
	{
		pParent->m_tKeys[i] = pParent->m_tKeys[i + 1];
		pParent->m_pChild[i + 1] = pParent->m_pChild[i + 2];
	}
	DeleteNode(pChild2);  //删除pChild2  
}

G_BTREE_TEMPLATE GINLINE
gvoid G_BTREE_QUAL::Recursive_remove(NodeT *pNode, const KeyT &key)
{
	gint i = 0;
	while (i<pNode->m_nKeyNum&&key>pNode->m_tKeys[i])
		++i;
	if (i < pNode->m_nKeyNum&&key == pNode->m_tKeys[i])//关键字key在节点pNode中  
	{
		if (pNode->m_bIsLeaf)//pNode是个叶节点  
		{
			//从pNode中删除k  
			--pNode->m_nKeyNum;
			for (; i < pNode->m_nKeyNum; ++i)
			{
				pNode->m_tKeys[i] = pNode->m_tKeys[i + 1];
			}
			return;
		}
		else//pNode是个内节点  
		{
			NodeT *pChildPrev = pNode->m_pChild[i];//节点pNode中前于key的子节点  
			NodeT *pChildNext = pNode->m_pChild[i + 1];//节点pNode中后于key的子节点  
			if (pChildPrev->m_nKeyNum >= CHILD_MIN)//节点pChildPrev中至少包含CHILD_MIN个关键字  
			{
				T prevKey = GetPredecessor(pChildPrev); //获取key的前驱关键字  
				Recursive_remove(pChildPrev, prevKey);
				pNode->m_tKeys[i] = prevKey;     //替换成key的前驱关键字  
				return;
			}
			else if (pChildNext->m_nKeyNum >= CHILD_MIN)//节点pChildNext中至少包含CHILD_MIN个关键字  
			{
				T nextKey = getSuccessor(pChildNext); //获取key的后继关键字  
				Recursive_remove(pChildNext, nextKey);
				pNode->m_tKeys[i] = nextKey;     //替换成key的后继关键字  
				return;
			}
			else//节点pChildPrev和pChildNext中都只包含CHILD_MIN-1个关键字  
			{
				MergeChild(pNode, i);
				Recursive_remove(pChildPrev, key);
			}
		}
	}
	else//关键字key不在节点pNode中  
	{
		NodeT *pChildNode = pNode->m_pChild[i];//包含key的子树根节点  
		if (pChildNode->m_nKeyNum == KEY_MIN)//只有t-1个关键字  
		{
			NodeT *pLeft = i > 0 ? pNode->m_pChild[i - 1] : NULL;  //左兄弟节点  
			NodeT *pRight = i < pNode->m_nKeyNum ? pNode->m_pChild[i + 1] : NULL;//右兄弟节点  
			gint j;
			if (pLeft&&pLeft->m_nKeyNum >= CHILD_MIN)//左兄弟节点至少有CHILD_MIN个关键字  
			{
				//父节点中i-1的关键字下移至pChildNode中  
				for (j = pChildNode->m_nKeyNum; j > 0; --j)
				{
					pChildNode->m_tKeys[j] = pChildNode->m_tKeys[j - 1];
				}
				pChildNode->m_tKeys[0] = pNode->m_tKeys[i - 1];

				if (!pLeft->m_bIsLeaf)
				{
					for (j = pChildNode->m_nKeyNum + 1; j > 0; --j) //pLeft节点中合适的子女指针移植到pChildNode中  
					{
						pChildNode->m_pChild[j] = pChildNode->m_pChild[j - 1];
					}
					pChildNode->m_pChild[0] = pLeft->m_pChild[pLeft->m_nKeyNum];
				}
				++pChildNode->m_nKeyNum;
				pNode->m_tKeys[i] = pLeft->m_tKeys[pLeft->m_nKeyNum - 1];//pLeft节点中的最大关键字上升到pNode中  
				--pLeft->m_nKeyNum;
			}
			else if (pRight&&pRight->m_nKeyNum >= CHILD_MIN)//右兄弟节点至少有CHILD_MIN个关键字  
			{
				//父节点中i的关键字下移至pChildNode中  
				pChildNode->m_tKeys[pChildNode->m_nKeyNum] = pNode->m_tKeys[i];
				++pChildNode->m_nKeyNum;
				pNode->m_tKeys[i] = pRight->m_tKeys[0];//pRight节点中的最小关键字上升到pNode中  
				--pRight->m_nKeyNum;
				for (j = 0; j < pRight->m_nKeyNum; ++j)
				{
					pRight->m_tKeys[j] = pRight->m_tKeys[j + 1];
				}
				if (!pRight->m_bIsLeaf)
				{
					pChildNode->m_pChild[pChildNode->m_nKeyNum] = pRight->m_pChild[0];//pRight节点中合适的子女指针移植到pChildNode中  
					for (j = 0; j <= pRight->m_nKeyNum; ++j)
					{
						pRight->m_pChild[j] = pRight->m_pChild[j + 1];
					}
				}
			}
			//左右兄弟节点都只包含CHILD_MIN-1个节点  
			else if (pLeft)//与左兄弟合并  
			{
				MergeChild(pNode, i - 1);
				pChildNode = pLeft;
			}
			else if (pRight)//与右兄弟合并  
			{
				MergeChild(pNode, i);

			}
		}
		Recursive_remove(pChildNode, key);
	}
}

G_BTREE_TEMPLATE GINLINE
KeyT &G_BTREE_QUAL::GetPredecessor(NodeT *pNode)
{
	while (!pNode->m_bIsLeaf)
	{
		pNode = pNode->m_pChild[pNode->m_nKeyNum];
	}
	return pNode->m_tKeys[pNode->m_nKeyNum - 1];
}

G_BTREE_TEMPLATE GINLINE
const KeyT &G_BTREE_QUAL::GetPredecessor(const NodeT *pNode) const
{
	while (!pNode->m_bIsLeaf)
	{
		pNode = pNode->m_pChild[pNode->m_nKeyNum];
	}
	return pNode->m_tKeys[pNode->m_nKeyNum - 1];
}

G_BTREE_TEMPLATE GINLINE
KeyT &G_BTREE_QUAL::GetSuccessor(NodeT *pNode)
{
	while (!pNode->m_bIsLeaf)
	{
		pNode = pNode->m_pChild[0];
	}
	return pNode->m_tKeys[0];
}

G_BTREE_TEMPLATE GINLINE
const KeyT &G_BTREE_QUAL::GetSuccessor(const NodeT *pNode) const
{
	while (!pNode->m_bIsLeaf)
	{
		pNode = pNode->m_pChild[0];
	}
	return pNode->m_tKeys[0];
}

#ifdef GDEBUG

G_BTREE_TEMPLATE GINLINE
gvoid G_BTREE_QUAL::Display() const
{
	DisplayInConcavo(m_pRoot, KEY_MAX * 10);
}

G_BTREE_TEMPLATE GINLINE
gvoid G_BTREE_QUAL::DisplayInConcavo(NodeT *pNode, gint count) const
{
	if (pNode != NULL)
	{
		gint i, j;
		for (i = 0; i < pNode->m_nKeyNum; ++i)
		{
			if (!pNode->m_bIsLeaf)
			{
				DisplayInConcavo(pNode->m_pChild[i], count - 2);
			}
			for (j = count; j >= 0; --j)
			{
				cout << "-";
			}
			cout << pNode->m_tKeys[i] << endl;
		}
		if (!pNode->m_bIsLeaf)
		{
			DisplayInConcavo(pNode->m_pChild[i], count - 2);
		}
	}
}

#endif // GDEBUG

} // namespace gsystem

#undef G_BTREE_QUAL
#undef G_BTREE_TEMPLATE

#endif // _CORE_B_TREE_INLINE_