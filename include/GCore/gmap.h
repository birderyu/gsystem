#ifndef _CORE_MAP_H_
#define _CORE_MAP_H_

#define G_MAP_USER_ORDER

#ifdef G_MAP_USER_ORDER
#include "gordermap.h"
template < typename KeyT,
	typename ValueT,
	typename CompareT = GCompareToF < KeyT >>
class GMap 
	: public GOrderMap<KeyT, ValueT, CompareT> {};
#else // !G_MAP_USER_ORDER
#include "gunordermap.h"
template < typename KeyT,
	typename ValueT>
class GMap 
	: public GUnorderMap<KeyT, ValueT> {};
#endif // G_MAP_USER_ORDER

#endif // _CORE_MAP_H_