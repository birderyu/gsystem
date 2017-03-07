#ifndef _CORE_B_TREE_H_
#define _CORE_B_TREE_H_

template<typename KeyT, typename ValueT, gsize KEY_MAX, gsize CHILD_MAX>
struct GBTreeNode
	: public GNewT<GBTreeNode<KeyT, ValueT, KEY_MAX, CHILD_MAX>>
{
	gbool m_bIsLeaf;					// 是否是叶子节点  
	gsize m_nKeyNum;					// 节点包含的关键字数量  
	KeyT m_tKeys[KEY_MAX];				// 关键字数组
	ValueT m_tValues[KEY_MAX];			// 值数组
	GBTreeNode *m_pChild[CHILD_MAX];	// 子树指针数组  

	GBTreeNode(gbool b = true, gsize n = 0)
		:m_bIsLeaf(b), m_nKeyNum(n) {}
};

template<typename KeyT,
	typename ValueT,
	gsize M = 3, 
	gsize KEY_MAX = 2 * M - 1, 
	gsize KEY_MIN = M - 1,
	gsize CHILD_MAX = KEY_MAX + 1, 
	hugsize CHILD_MIN = KEY_MIN + 1,
	typename NodeT = GBTreeNode<KeyT, ValueT, KEY_MAX, CHILD_MAX>>
class GBTree
{
public:
	GBTree()
	{
		m_pRoot = NULL;  //创建一棵空的B树  
	}

	~GBTree()
	{
		Clear();
	}

	gbool Insert(const KeyT &key, const ValueT &value)    //向B数中插入新结点key  
	{
		if (Contains(key))  //检查该关键字是否已经存在  
		{
			return false;
		}
		else
		{
			if (m_pRoot == NULL)//检查是否为空树  
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

	gbool Delete(const KeyT &key)    //从B中删除结点key  
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
				if (pChild1->m_nKeyNum == KEY_MIN&&pChild2->m_nKeyNum == KEY_MIN)
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
	gvoid Display()const //打印树的关键字  
	{
		DisplayInConcavo(m_pRoot, KEY_MAX * 10);
	}
	gbool Contains(const KeyT &key)const   //检查该key是否存在于B树中  
	{
		return Search(m_pRoot, key);
	}
	gvoid Clear()                      //清空B树  
	{
		Recursive_clear(m_pRoot);
		m_pRoot = NULL;
	}
private:
	//删除树  
	gvoid Recursive_clear(NodeT *pNode)
	{
		if (pNode != NULL)
		{
			if (!pNode->m_bIsLeaf)
			{
				for (int i = 0; i <= pNode->m_nKeyNum; ++i)
					Recursive_clear(pNode->m_pChild[i]);
			}
			DeleteNode(pNode);
		}
	}

	//删除节点  
	gvoid DeleteNode(NodeT *&pNode)
	{
		if (pNode != NULL)
		{
			delete pNode;
			pNode = NULL;
		}
	}

	//查找关键字  
	gbool Search(NodeT *pNode, const KeyT &key)const
	{
		if (pNode == NULL)  //检测节点指针是否为空，或该节点是否为叶子节点  
		{
			return false;
		}
		else
		{
			int i;
			for (i = 0; i<pNode->m_nKeyNum && key>*(pNode->m_tKeys + i); ++i)//找到使key<=pNode->keyValue[i]成立的最小下标i  
			{
			}
			if (i < pNode->m_nKeyNum && key == pNode->m_tKeys[i])
			{
				return true;
			}
			else
			{
				if (pNode->m_bIsLeaf)   //检查该节点是否为叶子节点  
				{
					return false;
				}
				else
				{
					return Search(pNode->m_pChild[i], key);
				}
			}
		}
	}

	//分裂子节点  
	gvoid SplitChild(NodeT *pParent, int nChildIndex, NodeT *pChild)
	{
		//将pChild分裂成pLeftNode和pChild两个节点  
		NodeT *pRightNode = new NodeT();//分裂后的右节点  
		pRightNode->m_bIsLeaf = pChild->m_bIsLeaf;
		pRightNode->m_nKeyNum = KEY_MIN;
		int i;
		for (i = 0; i < KEY_MIN; ++i)//拷贝关键字的值  
		{
			pRightNode->m_tKeys[i] = pChild->m_tKeys[i + CHILD_MIN];
		}
		if (!pChild->m_bIsLeaf)  //如果不是叶子节点，拷贝孩子节点指针  
		{
			for (i = 0; i < CHILD_MIN; ++i)
			{
				pRightNode->m_pChild[i] = pChild->m_pChild[i + CHILD_MIN];
			}
		}

		pChild->m_nKeyNum = KEY_MIN;  //更新左子树的关键字个数  

		for (i = pParent->m_nKeyNum; i > nChildIndex; --i)//将父节点中的nChildIndex后的所有关键字的值和子树指针向后移一位  
		{
			pParent->m_pChild[i + 1] = pParent->m_pChild[i];
			pParent->m_tKeys[i] = pParent->m_tKeys[i - 1];
		}
		++pParent->m_nKeyNum;  //更新父节点的关键字个数  
		pParent->m_pChild[nChildIndex + 1] = pRightNode;  //存储右子树指针  
		pParent->m_tKeys[nChildIndex] = pChild->m_tKeys[KEY_MIN];//把节点的中间值提到父节点  
	}

	//在非满节点中插入关键字  
	gvoid InsertNonFull(NodeT *pNode, const KeyT &key, const ValueT &value)
	{
		int i = pNode->m_nKeyNum;  //获取节点内关键字个数  
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
			InsertNonFull(pChild, key);  //插入关键字到目标子树节点  
		}
	}

	//用括号打印树  
	gvoid DisplayInConcavo(NodeT *pNode, int count)const
	{
		if (pNode != NULL)
		{
			int i, j;
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

	//合并两个子节点  
	gvoid MergeChild(NodeT *pParent, int index)
	{
		NodeT *pChild1 = pParent->m_pChild[index];
		NodeT *pChild2 = pParent->m_pChild[index + 1];
		//将pChild2数据合并到pChild1  
		pChild1->m_nKeyNum = KEY_MAX;
		pChild1->m_tKeys[KEY_MIN] = pParent->m_tKeys[index];//将父节点index的值下移  
		int i;
		for (i = 0; i < KEY_MIN; ++i)
		{
			pChild1->m_tKeys[i + KEY_MIN + 1] = pChild2->m_tKeys[i];
		}
		if (!pChild1->m_bIsLeaf)
		{
			for (i = 0; i < CHILD_MIN; ++i)
			{
				pChild1->m_pChild[i + CHILD_MIN] = pChild2->m_pChild[i];
			}
		}

		//父节点删除index的key，index后的往前移一位  
		--pParent->m_nKeyNum;
		for (i = index; i < pParent->m_nKeyNum; ++i)
		{
			pParent->m_tKeys[i] = pParent->m_tKeys[i + 1];
			pParent->m_pChild[i + 1] = pParent->m_pChild[i + 2];
		}
		DeleteNode(pChild2);  //删除pChild2  
	}

	//递归的删除关键字  
	gvoid Recursive_remove(NodeT *pNode, const KeyT &key)
	{
		int i = 0;
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
				int j;
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

	KeyT GetPredecessor(NodeT *pNode)//找到前驱关键字  
	{
		while (!pNode->m_bIsLeaf)
		{
			pNode = pNode->m_pChild[pNode->m_nKeyNum];
		}
		return pNode->m_tKeys[pNode->m_nKeyNum - 1];
	}

	KeyT GetSuccessor(NodeT *pNode)//找到后继关键字  
	{
		while (!pNode->m_bIsLeaf)
		{
			pNode = pNode->m_pChild[0];
		}
		return pNode->m_tKeys[0];
	}

private:
	NodeT * m_pRoot;  //B树的根节点  
};

#endif // _CORE_B_TREE_H_