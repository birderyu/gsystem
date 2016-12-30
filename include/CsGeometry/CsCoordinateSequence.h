#ifndef _GEOMETRY_COORDINATE_SEQUENCE_H_
#define _GEOMETRY_COORDINATE_SEQUENCE_H_

#include "CsObject.h"
#include "CsVector.h"
#include "CsCoordinate.h"

class CS_API CsCoordinateSequence
{
public:
	CsCoordinateSequence();
	CsCoordinateSequence(const CsCoordinate &);
	CsCoordinateSequence(const CsVector<CsCoordinate> &);
	CsCoordinateSequence(const CsVector<cs_real> &);
	CsCoordinateSequence(const CsCoordinateSequence &);

	CsCoordinate GetAt(cs_size_t pos) const;
	CsCoordinate operator[](cs_size_t pos) const;
	cs_void SetAt(cs_size_t pos, const CsCoordinate &);

	cs_real GetXAt(cs_size_t pos) const;
	cs_real &GetXAt(cs_size_t pos);
	cs_real GetYAt(cs_size_t pos) const;
	cs_real &GetYAt(cs_size_t pos);
	cs_real GetZAt(cs_size_t pos) const;
	cs_real &GetZAt(cs_size_t pos);

private:
	CsVector<cs_real> m_tCoords;
};

#endif // _GEOMETRY_COORDINATE_SEQUENCE_H_