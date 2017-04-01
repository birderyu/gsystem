#ifndef _CORE_B_TREE_H_
#define _CORE_B_TREE_H_

#include "gnew.h"

namespace gsystem { // gsystem

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
	gsize CHILD_MIN = KEY_MIN + 1,
	typename NodeT = GBTreeNode<KeyT, ValueT, KEY_MAX, CHILD_MAX>>
class GBTree
{
public:
	GBTree();
	~GBTree();

	// 向B树中插入新结点key 
	gbool Insert(const KeyT &key, const ValueT &value);

	// 从B树中删除结点key 
	gbool Delete(const KeyT &key);

	//检查该key是否存在于B树中
	gbool Contains(const KeyT &key) const;

	//清空B树
	gvoid Clear();

#ifdef GDEBUG
	// 打印树的关键字 
	gvoid Display() const;
#endif // GDEBUG

private:
	// 递归删除树  
	gvoid Recursive_clear(NodeT *pNode);

	// 删除节点  
	gvoid DeleteNode(NodeT *&pNode);

	// 查找关键字  
	gbool Search(NodeT *pNode, const KeyT &key) const;

	// 分裂子节点  
	gvoid SplitChild(NodeT *pParent, gint nChildIndex, NodeT *pChild);

	// 在非满节点中插入关键字  
	gvoid InsertNonFull(NodeT *pNode, const KeyT &key, const ValueT &value);

	// 合并两个子节点  
	gvoid MergeChild(NodeT *pParent, gsize index);

	// 递归的删除关键字  
	gvoid Recursive_remove(NodeT *pNode, const KeyT &key);

	// 找到前驱关键字  
	KeyT &GetPredecessor(NodeT *pNode);
	const KeyT &GetPredecessor(const NodeT *pNode) const;

	// 找到后继关键字  
	KeyT &GetSuccessor(NodeT *pNode);
	const KeyT &GetSuccessor(const NodeT *pNode) const;

#ifdef GDEBUG
	// 用括号打印树  
	gvoid DisplayInConcavo(NodeT *pNode, gint count) const;
#endif // GDEBUG

private:
	NodeT * m_pRoot;  //B树的根节点  
};

} // namespace gsystem

#include "gbtree.inl"

#endif // _CORE_B_TREE_H_