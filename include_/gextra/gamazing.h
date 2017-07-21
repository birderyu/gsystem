 #ifndef _CORE_AMAZING_H_
#define _CORE_AMAZING_H_

#include "gtype.h"

#ifdef G_NEED_ALL_FUNCTION

namespace gsystem { // gsystem

class GAPI GAmazing
{
	/// 快速求平方根的倒数
	gfloat FastInvSqrt(gfloat x)
	{
		gfloat xhalf = 0.5f * x;
		gint i = *(gint*)&x;
		i = 0x5f3759df - (i >> 1);
		x = *(gfloat*)&i;
		x = x*(1.5f - (xhalf*x*x));
		return x;
	}
};

} // namespace gsystem

#endif // G_NEED_ALL_FUNCTION

#endif // _CORE_AMAZING_H_