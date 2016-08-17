// 使用红黑树实现

#ifndef _CORE_MAP_H_
#define _CORE_MAP_H_

#include "CsRBTree.h"

/// 节点
template <typename KeyType, typename ValueType>
struct CsMapNode :public CsRBTreeNode<KeyType>
{
	ValueType m_tValue;
	CsMapNode(
		const KeyType &key = KeyType(),
		const ValueType &value = ValueType(),
		CsBTreeNode<KeyType> *parent = NULL,
		CsBTreeNode<KeyType> *left = NULL,
		CsBTreeNode<KeyType> *right = NULL,
		COLOR color = COLOR_BLACK);
	virtual ~CsMapNode();
	virtual CsBTreeNode<KeyType> *Copy() const;
};

template <typename KeyType, typename ValueType>
class CsMap :private CsRBTreeNode<KeyType>
{
public:
	void Insert(const KeyType &key, const ValueType &value);
};

template <typename KeyType, typename ValueType>
inline CsMapNode<KeyType, ValueType>::CsMapNode(
	const KeyType &key,
	const ValueType &value,
	CsBTreeNode<KeyType> *parent,
	CsBTreeNode<KeyType> *left,
	CsBTreeNode<KeyType> *right,
	COLOR color)
	: CsRBTreeNode(key, parent, left, right, color)
	, m_tValue(value)
{

}

template <typename KeyType, typename ValueType>
inline CsMapNode<KeyType, ValueType>::~CsMapNode()
{

}

template <typename KeyType, typename ValueType>
inline CsBTreeNode<KeyType> *CsMapNode<KeyType, ValueType>::Copy() const
{
	CsMapNode<KeyType, ValueType> *pNode = NULL;
	try
	{
		pNode = new CsMapNode<KeyType, ValueType>(m_tData, m_tValue, m_pParent, NULL, NULL, m_emColor);
	}
	catch (std::bad_alloc&)
	{
		pNode = NULL;
	}
	if (!pNode)
	{
		return NULL;
	}
	if (m_pLeft)
	{
		pNode->m_pLeft = m_pLeft->Copy();
	}
	if (m_pRight)
	{
		pNode->m_pRight = m_pRight->Copy();
	}
	return pNode;
}

#endif // _CORE_MAP_H_