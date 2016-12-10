#ifndef _CORE_MAP_H_
#define _CORE_MAP_H_

#define CS_MAP_USER_ORDER

#ifdef CS_MAP_USER_ORDER
#include "CsOrderMap.h"
template < typename KeyT,
	typename ValueT,
	typename CompareT = CsCompareF < KeyT >>
class CsMap 
	: public CsOrderMap<KeyT, ValueT, CompareT> {};
#else // !CS_MAP_USER_ORDER
#include "CsUnorderMap.h"
template < typename KeyT,
	typename ValueT>
class CsMap 
	: public CsUnorderMap<KeyT, ValueT> {};
#endif // CS_MAP_USER_ORDER

#endif // _CORE_MAP_H_