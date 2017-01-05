#include "CsGeometryFactory.h"
#include "CsPoint_Impl.h"

CsGeometryP CsGeometryFactory::CreatePoint2D(cs_real x, cs_real y) const
{
	return CsGeometryP(new CsPoint_Impl<2>(this, x, y));
}

#ifdef CS_GEOMETRY_HAS_Z
CsGeometryP CsGeometryFactory::CreatePoint3D(cs_real x, cs_real y, cs_real z) const
{
	return CsGeometryP(new CsPoint_Impl<3>(this, x, y, z));
}
#endif