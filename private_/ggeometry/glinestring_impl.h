#ifndef _GEOMETRY_LINE_STRING_IMPLEMENT_H_
#define _GEOMETRY_LINE_STRING_IMPLEMENT_H_

#include "glinestring.h"

namespace gsystem { // gsystem
namespace detail { // gsystem.detail
namespace geom { // gsystem.detail.geom

template<gsize DIMENSION>
class GLineString_Impl
	: virtual public GLineString
{
public:
	GLineString_Impl(const GGeometryFactory *factory);
	GLineString_Impl(const GGeometryFactory *factory, GCoordinate *coords, gsize size);
	GLineString_Impl(const GGeometryFactory *factory, const GArray<GCoordinate> &coords);
	GLineString_Impl(const GGeometryFactory *factory, const GCoordinateSequence &coords);
	GLineString_Impl(const GLineString_Impl<DIMENSION> &l);

private:
	GSinglePoint_Store<DIMENSION> m_tStore;
	const GGeometryFactory *m_pFactory;
};

} // namespace gsystem.detail.geom
} // namespace gsystem.detail
} // namespace gsystem

#endif // _GEOMETRY_LINE_STRING_IMPLEMENT_H_
