#ifndef _GEOMETRY_POLYLINE_STORE_H_
#define _GEOMETRY_POLYLINE_STORE_H_

#include "CsGeometryGlobal.h"

class CsPolyline_Store_2D
{
public:
	cs_bool Initialize();
	cs_bool Initialize(cs_size_t);
	cs_bool Initialize(cs_size_t, cs_real defaultX, cs_real defaultY);
	cs_bool Initialize(const CsPolyline_Store_2D &);

	cs_size_t PointCount();

	cs_real &GetXAt(cs_size_t pos);
	cs_real  GetXAt(cs_size_t pos) const;
	cs_real &GetYAt(cs_size_t pos);
	cs_real  GetYAt(cs_size_t pos) const;

	cs_void SetXAt(cs_size_t pos, cs_real x) const;
	cs_void SetYAt(cs_size_t pos, cs_real y) const;

private:
	cs_size_t m_nPointCount;
	cs_real *m_pCoords;
};

#endif // _GEOMETRY_POLYLINE_STORE_H_