/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	ghuffmantree.h
** @brief	¹þ·òÂüÊ÷µÄ¶¨Òå
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2016-12-5
** @version	0.1
**
****************************************************************************/

#ifndef _CORE_HUFFMAN_TREE_H_
#define _CORE_HUFFMAN_TREE_H_

#include "gbinarytree.h"
#include "gbinaryheap.h"

template<typename DataT>
class GHuffmanTreeNode 
	: public GBinaryTreeNodeT<GHuffmanTreeNode<DataT>>
	, public GDataNodeT<DataT>
	, public GNewT<GHuffmanTreeNode<DataT>>
{
	GHuffmanTreeNode(
		const DataT &data = DataT(),
		GReadBlackTreeNode<DataT> *parent = GNULL,
		GReadBlackTreeNode<DataT> *left = GNULL,
		GReadBlackTreeNode<DataT> *right = GNULL)
		: GBinaryTreeNodeT<GHuffmanTreeNode<DataT>>(parent, left, right)
		, GDataNodeT<DataT>(data)
	{

	}
};

template<typename DataT,
	typename CompareT = GLessThanF<DataT>>
class GHuffmanTree
	: GBinaryTree<GReadBlackTreeNode<DataT>>
{
public:
	GHuffmanTree();
	gvoid Append(const GArray<DataT> &arr);
	gvoid Append(const GArray<DataT> &arr, gsize start, gsize size);
	gvoid Append(DataT *arr, gsize arr_size);
	gvoid Append(DataT *arr, gsize start, gsize size);
};

#endif // _CORE_HUFFMAN_TREE_H_