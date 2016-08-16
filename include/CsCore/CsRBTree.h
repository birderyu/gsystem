#ifndef _CSCORE_RED_BLACK_TREE_H_
#define _CSCORE_RED_BLACK_TREE_H_

#include "CsBSTree.h"

template<typename T>
class CsRBTree;

template<typename T>
class CsRBTreeNode :public CsBTreeNode<T>
{
	friend class CsRBTree<T>;

public:
	enum EM_RBTREENODE_COLOR 
	{ 
		RBTREENODE_COLOR_RED = 0,
		RBTREENODE_COLOR_BLACK = 1
	};

public:
	EM_RBTREENODE_COLOR GetColor() const;
	void SetColor(EM_RBTREENODE_COLOR emColor);
	
private:
	EM_RBTREENODE_COLOR emColor;
};

template<typename T>
class CsRBTree : public CsBSTree<T>
{

};

#endif // _CSCORE_RED_BLACK_TREE_H_