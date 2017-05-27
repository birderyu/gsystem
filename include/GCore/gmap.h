#ifndef _CORE_MAP_H_
#define _CORE_MAP_H_

#define G_MAP_USER_ORDER

#ifdef G_MAP_USER_ORDER
#include "gsortedmap.h"
namespace gsystem { // gsystem
template < typename KeyT,
	typename ValueT,
	typename CompareT = GCompareToF < KeyT >>
class GMap final
	: public GSortedMap<KeyT, ValueT, CompareT> {};
} // namespace gsystem
#else // !G_MAP_USER_ORDER
#include "gunordermap.h"
namespace gsystem { // gsystem
template < typename KeyT, typename ValueT,
	typename HashT = GHashF<KeyT>,
	typename CompareT = GEqualToF<KeyT>>
class GMap final
	: public GUnorderMap<KeyT, ValueT, HashT, CompareT> {};
} // namespace gsystem
#endif // G_MAP_USER_ORDER

#endif // _CORE_MAP_H_