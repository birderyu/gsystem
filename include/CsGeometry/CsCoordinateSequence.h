#ifndef _GEOMETRY_COORDINATE_SEQUENCE_H_
#define _GEOMETRY_COORDINATE_SEQUENCE_H_

#include "gobject.h"
#include "gvector.h"
#include "CsCoordinate.h"

class GAPI CsCoordinateSequence
{
public:
	CsCoordinateSequence();
	CsCoordinateSequence(greal x, greal y);
	CsCoordinateSequence(greal x, greal y, greal z);
	CsCoordinateSequence(const CsCoordinate &);
	CsCoordinateSequence(const GVector<CsCoordinate> &);
	CsCoordinateSequence(const GVector<greal> &);
	CsCoordinateSequence(const CsCoordinateSequence &);

	CsCoordinate GetAt(gsize pos) const;
	CsCoordinate operator[](gsize pos) const;
	gvoid SetAt(gsize pos, const CsCoordinate &);

	greal GetXAt(gsize pos) const;
	greal &GetXAt(gsize pos);
	greal GetYAt(gsize pos) const;
	greal &GetYAt(gsize pos);
	greal GetZAt(gsize pos) const;
	greal &GetZAt(gsize pos);

private:
	GVector<greal> m_tCoords;
};

#endif // _GEOMETRY_COORDINATE_SEQUENCE_H_