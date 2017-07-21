#ifndef _CORE_LINKED_LIST_INLINE_
#define _CORE_LINKED_LIST_INLINE_

namespace gsystem { // gsystem

template<typename T, typename NodeT> GINLINE
T &GLinkedList<T, NodeT>::operator[](gsize pos)
{
	return GetValueAt(pos);
}

template<typename T, typename NodeT> GINLINE
const T &GLinkedList<T, NodeT>::operator[](gsize pos) const
{
	return GetValueAt(pos);
}

}  // namespace gsystem

#endif // _CORE_LINKED_LIST_INLINE_
