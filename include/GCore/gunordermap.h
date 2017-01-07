#ifndef _CORE_UNORDER_MAP_H_
#define _CORE_UNORDER_MAP_H_

#include "ghashtable.h"

template <typename KeyT, typename ValueT,
	typename HashT = GHashF<KeyT>,
	typename CompareT = GEqualToF < KeyT >>
class GUnorderMap
	: public GObject
{

};

#endif // _CORE_UNORDER_MAP_H_