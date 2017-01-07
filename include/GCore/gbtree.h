#ifndef _CORE_B_TREE_H_
#define _CORE_B_TREE_H_

#include "gobject.h"
#include "gdynamicarray.h"
#include "greadblacktree.h"

template<typename KeyT,
	typename CompareT = GCompareToF<KeyT >>
class GBTreeNode 
	: public GObject
{
public:
	GBTreeNode();
	virtual ~GBTreeNode();

	KeyT &GetKeyAt(const gsize id);
	gpointer GetChildAt(const gsize id);

private:
	GBTreeNode<KeyT> *m_pParent;		// Ë«Ç×
	GDynamicArray<gpointer> m_tChildren;		// º¢×Ó
	GReadBlackTree<KeyT, CompareT> m_tKeys;	// Ê¹ÓÃºìºÚÊ÷ÅÅÐòµÄ¹Ø¼ü×Ö£¿
};

template<typename KeyT,
	gsize LevelN = 3,
	typename CompareT = GCompareToF<KeyT >,
	typename NodeT = GBTreeNode<KeyT>>
class GBTree 
	: public GObject
{

};

#endif // _CORE_B_TREE_H_