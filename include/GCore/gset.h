#ifndef _CORE_SET_H_
#define _CORE_SET_H_

#define G_SET_USER_UNORDER

#ifdef G_SET_USER_UNORDER

#include "gunorderset.h"

namespace gsystem { // gsystem
template < typename KeyT,
	typename HashT = GHashF<KeyT>,
	typename CompareT = GEqualToF<KeyT>>
class GSet final
	: public GUnorderSet<KeyT, HashT, CompareT> {};
} // namespace gsystem

#else // !G_SET_USER_UNORDER

#include "gorderset.h"

namespace gsystem { // gsystem
template < typename KeyT,
	typename CompareT = GCompareToF < KeyT >>
class GSet final
	: public GOrderSet<KeyT, CompareT> {};
} // namespace gsystem

#endif // G_SET_USER_UNORDER

#endif // _CORE_SET_H_