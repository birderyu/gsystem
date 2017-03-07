// 位操作封装类
#ifndef _CORE_BIT_SET_H_
#define _CORE_BIT_SET_H_

#include "gglobal.h"

template<gsize SIZE>
class GBitSet
{
public:
	GBitSet(gulong n = 0);
	GBitSet(const GBitSet<SIZE> &bitset);
	GBitSet(GBitSet<SIZE> &&bitset);

	gbool GetAt(gsize pos) const;
};

#endif // _CORE_BIT_SET_H_