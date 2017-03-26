#include "ggeometryfactory.h"
#include "gpoint_impl.h"

GGeometryPtr GGeometryFactory::CreatePoint2D(greal x, greal y) const
{
	return GGeometryPtr(new GPoint_Impl<2>(this, x, y));
}

#ifdef G_GEOMETRY_HAS_Z
GGeometryPtr GGeometryFactory::CreatePoint3D(greal x, greal y, greal z) const
{
	return GGeometryPtr(new GPoint_Impl<3>(this, x, y, z));
}
#endif