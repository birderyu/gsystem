/****************************************************************************
**
** Supernova
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
	typename CompareT = CsCompareF<DataT >>
class CsHuffmanTree 
	: CsBinaryTree<CsReadBlackTreeNode<DataT>>
{

};

#endif // _CORE_HUFFMAN_TREE_H_