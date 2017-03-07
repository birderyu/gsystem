#ifndef _CORE_TUPLE_INLINE_
#define _CORE_TUPLE_INLINE_

//////////////////////////////////////////////////////////////////////////

template<typename T1, typename T2>
GINLINE GPair<T1, T2>::GPair()
{

}

template<typename T1, typename T2>
GINLINE GPair<T1, T2>::GPair(const T1 &first, const T2 &second)
	: m_tFirst(first), m_tSecond(second)
{

}

template<typename T1, typename T2>
GINLINE GPair<T1, T2>::GPair(const T1 &first, T2 &&second)
	: m_tFirst(first), m_tSecond(GForward<T2>(second))
{

}

template<typename T1, typename T2>
GINLINE GPair<T1, T2>::GPair(T1 &&first, const T2 &second)
	: m_tFirst(GForward<T1>(first)), m_tSecond(second)
{

}

template<typename T1, typename T2>
GINLINE GPair<T1, T2>::GPair(T1 &&first, T2 &&second)
	: m_tFirst(GForward<T1>(first)), m_tSecond(GForward<T2>(second))
{

}

template<typename T1, typename T2>
GINLINE GPair<T1, T2>::GPair(const GPair<T1, T2> &pair)
	: m_tFirst(pair.m_tFirst), m_tSecond(pair.m_tFirst)
{

}

template<typename T1, typename T2>
GINLINE GPair<T1, T2>::GPair(GPair<T1, T2> &&pair)
	: m_tFirst(GMove(pair.m_tFirst)), m_tSecond(GMove(pair.m_tFirst))
{

}

template<typename T1, typename T2>
GINLINE const T1 &GPair<T1, T2>::First() const
{
	return m_tFirst;
}

template<typename T1, typename T2>
GINLINE T1 &GPair<T1, T2>::First()
{
	return m_tFirst;
}

template<typename T1, typename T2>
GINLINE const T2 &GPair<T1, T2>::Second() const
{
	return m_tFirst;
}

template<typename T1, typename T2>
GINLINE T2 &GPair<T1, T2>::Second()
{
	return m_tSecond;
}

template<typename T1, typename T2>
GINLINE GPair<T1, T2> GMakePair(const T1 &first, const T2 &second)
{
	return GPair<T1, T2>(first, second);
}

template<typename T1, typename T2>
GINLINE GPair<T1, T2> GMakePair(const T1 &first, T2 &&second)
{
	return GPair<T1, T2>(first, GForward<T2>(second));
}

template<typename T1, typename T2>
GINLINE GPair<T1, T2> GMakePair(T1 &&first, const T2 &second)
{
	return GPair<T1, T2>(GForward<T1>(first), second);
}

template<typename T1, typename T2>
GINLINE GPair<T1, T2> GMakePair(T1 &&first, T2 &&second)
{
	return GPair<T1, T2>(GForward<T1>(first), GForward<T2>(second));
}

//////////////////////////////////////////////////////////////////////////

#endif // _CORE_TUPLE_INLINE_
