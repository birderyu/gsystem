#include "CsGeometryFactory.h"
#include "CsPoint_Impl.h"

CsPointP CsGeometryFactory::CreatePoint(cs_real x, cs_real y) const
{
	return CsPointP(new CsPoint_Impl(this, x, y));
}
