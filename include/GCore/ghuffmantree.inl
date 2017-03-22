#ifndef _CORE_HUFFMAN_TREE_INLINE_
#define _CORE_HUFFMAN_TREE_INLINE_

#include "gbinaryheap.h"

namespace gsystem { // gsystem

template<typename DataT, typename CompareT>
typename GHuffmanTree<DataT, CompareT>::HuffmanCompareF GHuffmanTree<DataT, CompareT>::m_fCompare;

template<typename DataT, typename CompareT> GINLINE 
gvoid GHuffmanTree<DataT, CompareT>::Append(const GArray<DataT> &arr, gsize start, gsize size)
{
	GBinaryHeap<GHuffmanTreeNode<DataT> *, HuffmanCompareF> heap;
	for (gsize i = start; i < start + size; i++)
	{
		GHuffmanTreeNode<DataT> *node = new GHuffmanTreeNode<DataT>(arr[i]);
		heap.Insert(node);
	}
	while (heap.Size() > 1)
	{
		GHuffmanTreeNode<DataT> *left = heap.Top();
		heap.Pop();

		GHuffmanTreeNode<DataT> *right = heap.Top();
		heap.Pop();

		GHuffmanTreeNode<DataT> *parent = new GHuffmanTreeNode<DataT>(
			left->m_tData + right->m_tData, GNULL, left, right);
		left->m_pParent = right->m_pParent = parent;
		heap.Insert(parent);
	}
	GHuffmanTreeNode<DataT> *root = heap.Top();
	SetRoot(root);
}

}

#endif // _CORE_HUFFMAN_TREE_INLINE_
