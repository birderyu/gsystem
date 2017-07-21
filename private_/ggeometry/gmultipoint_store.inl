#ifndef _GEOMETRY_MULTI_POINT_STORE_INLINE_
#define _GEOMETRY_MULTI_POINT_STORE_INLINE_

namespace gsystem { // gsystem
namespace detail { // gsystem.detail
namespace geom { // gsystem.detail.geom

template<gsize DIMENSION> GINLINE
GMultiPoint_Store<DIMENSION>::GMultiPoint_Store(const greal *coords_d, gsize size)
	: m_aCoord(coords_d, size)
{
	GASSERT(size % DIMENSION == 0);
}

template<gsize DIMENSION> GINLINE
GMultiPoint_Store<DIMENSION>::GMultiPoint_Store(const GArray<greal> &coords_d)
{
	gsize coords_d_size = coords_d
	for (gsize i = 0; i <coords_d)
}

GMultiPoint_Store(GCoordinate *coords, gsize size);
GMultiPoint_Store(GCoordinate *coords, gsize size);
GMultiPoint_Store(const GArray<GCoordinate> &coords);


} // namespace gsystem.detail.geom
} // namespace gsystem.detail
} // namespace gsystem

#endif // _GEOMETRY_MULTI_POINT_STORE_INLINE_