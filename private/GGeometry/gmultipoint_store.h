#ifndef _GEOMETRY_MULTI_POINT_STORE_H_
#define _GEOMETRY_MULTI_POINT_STORE_H_

#include "ggeodef.h"
#include "gcoordinate.h"
#include "GCore/gseries.h"

namespace gsystem { // gsystem
namespace detail { // gsystem.detail
namespace geom { // gsystem.detail.geom

template<gsize DIMENSION>
class GMultiPoint_Store
{
public:
	GMultiPoint_Store(const greal *coords_d, gsize size);
	GMultiPoint_Store(const GArray<greal> &coords_d);
	GMultiPoint_Store(GCoordinate *coords, gsize size);
	GMultiPoint_Store(GCoordinate *coords, gsize size);
	GMultiPoint_Store(const GArray<GCoordinate> &coords);

	gbool IsEmpty() const;
	gsize Size() const;

	greal &X(gsize pos);
	greal  X(gsize pos) const;
	greal &Y(gsize pos);
	greal  Y(gsize pos) const;
	greal &Z(gsize pos);
	greal  Z(gsize pos) const;

	GDynamicArray<GCoordinate> Coordinates() const;
	GCoordinateSequence CoordinateSequence() const;

	gvoid SetX(gsize pos, greal x);
	gvoid SetY(gsize pos, greal y);
	gvoid SetZ(gsize pos, greal z);
	gvoid SetCoordinate(gsize pos, const GCoordinate &c);

private:
	GSeries<greal, DIMENSION * 2, false, 0> m_aCoord;
};

} // namespace gsystem.detail.geom
} // namespace gsystem.detail
} // namespace gsystem

#include "gmultipoint_store.inl"

#endif // _GEOMETRY_MULTI_POINT_STORE_H_