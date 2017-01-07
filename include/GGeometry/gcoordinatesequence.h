#ifndef _GEOMETRY_COORDINATE_SEQUENCE_H_
#define _GEOMETRY_COORDINATE_SEQUENCE_H_

#include "GCore/gobject.h"
#include "GCore/gvector.h"
#include "gcoordinate.h"

class GAPI GCoordinateSequence
{
public:
	GCoordinateSequence();
	GCoordinateSequence(greal x, greal y);
	GCoordinateSequence(greal x, greal y, greal z);
	GCoordinateSequence(const GCoordinate &);
	GCoordinateSequence(const GVector<GCoordinate> &);
	GCoordinateSequence(const GVector<greal> &);
	GCoordinateSequence(const GCoordinateSequence &);

	GCoordinate GetAt(gsize pos) const;
	GCoordinate operator[](gsize pos) const;
	gvoid SetAt(gsize pos, const GCoordinate &);

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