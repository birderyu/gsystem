#ifndef _GEOMETRY_SINGLE_POINT_STORE_H_
#define _GEOMETRY_SINGLE_POINT_STORE_H_

#include "ggeodef.h"
#include "gcoordinate.h"

namespace gsystem { // gsystem
namespace detail { // gsystem.detail
namespace geom { // gsystem.detail.geom

template<gsize DIMENSION>
class GSinglePoint_Store
{
public:
	enum { COORD_VALUE_SIZE = DIMENSION, };

public:
	GSinglePoint_Store();
	GSinglePoint_Store(greal x);
	GSinglePoint_Store(greal x, greal y);
	GSinglePoint_Store(greal x, greal y, greal z);
	GSinglePoint_Store(const GCoordinate &c);
	GSinglePoint_Store(const GSinglePoint_Store<DIMENSION> &p_s);
	GSinglePoint_Store(GSinglePoint_Store<DIMENSION> &&p_s);

	greal &X();
	greal  X() const;
	greal &Y();
	greal  Y() const;
	greal &Z();
	greal  Z() const;
	GCoordinate Coordinate() const;

	gvoid SetX(greal x);
	gvoid SetY(greal y);
	gvoid SetZ(greal z);
	gvoid SetCoordinate(const GCoordinate &c);

private:
	greal m_aCoord[COORD_VALUE_SIZE];
};

} // namespace gsystem.detail.geom
} // namespace gsystem.detail
} // namespace gsystem

#include "gsinglepoint_store.inl"

#endif // _GEOMETRY_SINGLE_POINT_STORE_H_
