/****************************************************************************
**
** GSystem: A quick, micro library of C++
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

namespace gsystem { // gsystem

template<typename DataT>
class GHuffmanTreeNode 
	: public GBinaryTreeNodeT<GHuffmanTreeNode<DataT>>
	, public GDataNodeT<DataT>
	, public GNewT<GHuffmanTreeNode<DataT>>
{
	GHuffmanTreeNode(
		const DataT &data = DataT(),
		GHuffmanTreeNode<DataT> *parent = GNULL,
		GHuffmanTreeNode<DataT> *left = GNULL,
		GHuffmanTreeNode<DataT> *right = GNULL)
		: GBinaryTreeNodeT<GHuffmanTreeNode<DataT>>(parent, left, right)
		, GDataNodeT<DataT>(data)
	{

	}
};

template<typename DataT,
	typename CompareT = GLessThanF<DataT>>
class GHuffmanTree
	: GBinaryTree<GHuffmanTreeNode<DataT>>
{
private:
	struct HuffmanCompareF
	{
		gbool operator()(const GHuffmanTreeNode<DataT> *left, 
			const GHuffmanTreeNode<DataT> *right) const
		{
			CompareT compareF;
			return compareF(left->m_tData < right->m_tData);
		}
	};

public:
	gvoid Append(const GArray<DataT> &arr);
	gvoid Append(const GArray<DataT> &arr, gsize start, gsize size);
	gvoid Append(DataT *arr, gsize arr_size);
	gvoid Append(DataT *arr, gsize start, gsize size);

private:
	static HuffmanCompareF m_fCompare;
};

} // namespace gsystem

#include "ghuffmantree.inl"

#endif // _CORE_HUFFMAN_TREE_H_