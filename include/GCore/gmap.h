#ifndef _CORE_MAP_H_
#define _CORE_MAP_H_

#define G_MAP_USER_ORDER

#ifdef G_MAP_USER_ORDER
#include "gordermap.h"
template < typename KeyT,
	typename ValueT,
	typename CompareT = GCompareToF < KeyT >>
class GMap final
	: public GOrderMap<KeyT, ValueT, CompareT> {};
#else // !G_MAP_USER_ORDER
#include "gunordermap.h"
template < typename KeyT, typename ValueT,
	typename HashT = GHashF<KeyT>,
	typename CompareT = GEqualToF<KeyT>>
class GMap final
	: public GUnorderMap<KeyT, ValueT, HashT, CompareT> {};
#endif // G_MAP_USER_ORDER

#endif // _CORE_MAP_H_