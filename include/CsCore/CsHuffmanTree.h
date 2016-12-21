/****************************************************************************
**
** CNova: A quick, micro library of C++
**
** @file	CsHuffman.h
** @brief	¹þ·òÂüÊ÷µÄ¶¨Òå
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2016-12-5
** @version	0.1
** @see		CsHuffman
**
****************************************************************************/

#ifndef _CORE_HUFFMAN_TREE_H_
#define _CORE_HUFFMAN_TREE_H_

#include "CsBinaryTree.h"
#include "CsBinaryHeap.h"

template<typename DataT>
class CsHuffmanTreeNode 
	: public CsBinaryTreeNodeT<CsHuffmanTreeNode<DataT>>
	, public CsDataNodeT<DataT>
	, public CsNewT<CsHuffmanTreeNode<DataT>>
{
	CsHuffmanTreeNode(
		const DataT &data = DataT(),
		CsReadBlackTreeNode<DataT> *parent = NULL,
		CsReadBlackTreeNode<DataT> *left = NULL,
		CsReadBlackTreeNode<DataT> *right = NULL)
		: CsBinaryTreeNodeT<CsHuffmanTreeNode<DataT>>(parent, left, right)
		, CsDataNodeT<DataT>(data)
	{

	}
};

template<typename DataT,
	typename CompareT = CsLessThanF<DataT>>
class CsHuffmanTree
	: CsBinaryTree<CsReadBlackTreeNode<DataT>>
{
public:
	CsHuffmanTree();
	cs_void Append(const CsArray<DataT> &arr);
	cs_void Append(const CsArray<DataT> &arr, cs_size_t start, cs_size_t size);
	cs_void Append(DataT *arr, cs_size_t arr_size);
	cs_void Append(DataT *arr, cs_size_t start, cs_size_t size);
};

#endif // _CORE_HUFFMAN_TREE_H_