#ifndef _CORE_STRUCTURE_INLINE_
#define _CORE_STRUCTURE_INLINE_

namespace gsystem { // gsystem

//////////////////////////////////////////////////////////////////////////
template<typename T> GINLINE
GPreviousNodeT<T>::GPreviousNodeT(T *previous) GNOEXCEPT
	: m_pPrevious(previous)
{

}


//////////////////////////////////////////////////////////////////////////
template<typename T> GINLINE
GNextNodeT<T>::GNextNodeT(T *next) GNOEXCEPT
	: m_pNext(next)
{

}

//////////////////////////////////////////////////////////////////////////
template<typename T> GINLINE
GPreviousNextNodeT<T>::GPreviousNextNodeT(T *previous, T *next) GNOEXCEPT
	: GPreviousNodeT<T>(previous)
	, GNextNodeT<T>(next)
{

}

//////////////////////////////////////////////////////////////////////////
template<typename T> GINLINE 
GBinTreeNodeT<T>::GBinTreeNodeT(T *parent, T *left, T *right) GNOEXCEPT
: m_pParent(parent), m_pLeft(left), m_pRight(left)
{

}

template<typename T> GINLINE 
const T *GBinTreeNodeT<T>::LeftSibling() const GNOEXCEPT
{
	if (m_pParent)
	{
		return m_pParent->m_pLeft;
	}
	return GNULL;
}

template<typename T> GINLINE 
const T *GBinTreeNodeT<T>::RightSibling() const GNOEXCEPT
{
	if (m_pParent)
	{
		return m_pParent->m_pRight;
	}
	return GNULL;
}

template<typename T> GINLINE 
const T *GBinTreeNodeT<T>::Next() const GNOEXCEPT
{
	const T *node = GNULL;
	if (m_pRight)
	{
		node = m_pRight;
		while (node->m_pLeft)
		{
			node = node->m_pLeft;
		}
	}
	else
	{
		if (!m_pParent)
		{
			return GNULL;
		}
		node = (const T *) this;
		const T *pnode = node->m_pParent;
		while (pnode && node == pnode->m_pRight)
		{
			node = pnode;
			pnode = node->m_pParent;
		}
		node = pnode;
	}
	return node;
}

template<typename T> GINLINE 
T *GBinTreeNodeT<T>::Next() GNOEXCEPT
{
	T *node = GNULL;
	if (m_pRight)
	{
		node = m_pRight;
		while (node->m_pLeft)
		{
			node = node->m_pLeft;
		}
	}
	else
	{
		if (!m_pParent)
		{
			return GNULL;
		}
		node = (T *) this;
		T *pnode = node->m_pParent;
		while (pnode && node == pnode->m_pRight)
		{
			node = pnode;
			pnode = node->m_pParent;
		}
		node = pnode;
	}
	return node;
}

template<typename T> GINLINE 
const T *GBinTreeNodeT<T>::Previous() const GNOEXCEPT
{
	const T *node = GNULL;
	if (m_pLeft)
	{
		node = m_pLeft;
		while (node->m_pRight)
		{
			node = node->m_pRight;
		}
	}
	else
	{
		if (!m_pParent)
		{
			return GNULL;
		}
		node = (const T *) this;
		const T *pnode = node->m_pParent;
		while (pnode && node == pnode->m_pLeft)
		{
			node = pnode;
			pnode = node->m_pParent;
		}
		node = pnode;
	}
	return node;
}

template<typename T> GINLINE 
T *GBinTreeNodeT<T>::Previous() GNOEXCEPT
{
	T *node = GNULL;
	if (m_pLeft)
	{
		node = m_pLeft;
		while (node->m_pRight)
		{
			node = node->m_pRight;
		}
	}
	else
	{
		if (!m_pParent)
		{
			return GNULL;
		}
		node = (T *) this;
		T *pnode = node->m_pParent;
		while (pnode && node == pnode->m_pLeft)
		{
			node = pnode;
			pnode = node->m_pParent;
		}
		node = pnode;
	}
	return node;
}

template<typename T> GINLINE 
const T *GBinTreeNodeT<T>::First() const GNOEXCEPT
{
	if (!m_pLeft)
	{
		return (const T *)this;
	}
	const T *node = (const T *)this;
	while (node->m_pLeft)
	{
		node = node->m_pLeft;
	}
	return node;
}

template<typename T> GINLINE 
T *GBinTreeNodeT<T>::First() GNOEXCEPT
{
	if (!m_pLeft)
	{
		return (T *) this;
	}
	T *node = (T *) this;
	while (node->m_pLeft)
	{
		node = node->m_pLeft;
	}
	return node;
}

template<typename T> GINLINE 
const T *GBinTreeNodeT<T>::Last() const GNOEXCEPT
{
	if (!m_pRight)
	{
		return (const T *) this;
	}
	const T *node = (const T *) this;
	while (node->m_pRight)
	{
		node = node->m_pRight;
	}
	return node;
}

template<typename T> GINLINE 
T *GBinTreeNodeT<T>::Last() GNOEXCEPT
{
	if (!m_pRight)
	{
		return (T *)this;
	}
	T *node = (T *)this;
	while (node->m_pRight)
	{
		node = node->m_pRight;
	}
	return node;
}

//////////////////////////////////////////////////////////////////////////
template<typename T>
GINLINE GValueNodeT<T>::GValueNodeT(const T &value) GNOEXCEPT
	: m_tData(value)
{

}

template<typename T>
GINLINE GValueNodeT<T>::GValueNodeT(T &&value) GNOEXCEPT
	: m_tData(GForward<T>(value))
{

}

//////////////////////////////////////////////////////////////////////////
template<typename T>
GINLINE GChildNodeT<T>::GChildNodeT(const T *child) GNOEXCEPT
	: m_pChild(child)
{

}

//////////////////////////////////////////////////////////////////////////
template<typename KeyT, typename ValueT>
GINLINE GPairNodeT<KeyT, ValueT>::GPairNodeT(const KeyT &key, const ValueT &value) GNOEXCEPT
	: m_tKey(key)
	, m_tValue(value)
{

}

template<typename KeyT, typename ValueT>
GINLINE GPairNodeT<KeyT, ValueT>::GPairNodeT(const KeyT &key, ValueT &&value) GNOEXCEPT
	: m_tKey(key)
	, m_tValue(GForward<ValueT>(value))
{

}

} // namespace gsystem

#endif // _CORE_STRUCTURE_INLINE_