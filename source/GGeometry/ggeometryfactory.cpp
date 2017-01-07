#include "ggeometryfactory.h"
#include "gpoint_impl.h"

GGeometryP GGeometryFactory::CreatePoint2D(greal x, greal y) const
{
	return GGeometryP(new GPoint_Impl<2>(this, x, y));
}

#ifdef G_GEOMETRY_HAS_Z
GGeometryP GGeometryFactory::CreatePoint3D(greal x, greal y, greal z) const
{
	return GGeometryP(new GPoint_Impl<3>(this, x, y, z));
}
#endif