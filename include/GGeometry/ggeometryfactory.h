#ifndef _GEOMETRY_GEOMETRY_FACTORY_H_
#define _GEOMETRY_GEOMETRY_FACTORY_H_

#include "ggeometry.h"

namespace gsystem { // gsystem
namespace geom { // gsystem.geom

class GAPI GGeometryFactory 
{
public:
	GGeometryPtr CreateGeometry() const;
	GGeometryCollection CreateGeometryCollection() const;

	GGeometryPtr CreatePoint() const;
	
	GGeometryPtr CreatePolygon() const;
	GGeometryPtr CreateMultiPoint() const;
	GGeometryPtr CreateMultiLineString() const;
	GGeometryPtr CreateMultiPolygon() const;

	GGeometryPtr CreatePoint2D(greal x, greal y) const;
	GGeometryPtr CreatePoint2D(const GCoordinate &coord) const;
	GGeometryPtr CreateLineString(GCoordinate *coords, gsize size) const;
	GGeometryPtr CreateLineString(const GArray<GCoordinate> &coords) const;
	GGeometryPtr CreateLineString(const GCoordinateSequence &coords) const;

#ifdef G_GEOMETRY_HAS_Z
	GGeometryPtr CreatePoint3D(greal x, greal y, greal z) const;
	GGeometryPtr CreatePoint3D(const GCoordinate &coord) const;
#endif
};

}
}

#endif // _GEOMETRY_GEOMETRY_FACTORY_H_