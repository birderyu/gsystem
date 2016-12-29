#ifndef _GEOMETRY_COORDINATE_SEQUENCE_H_
#define _GEOMETRY_COORDINATE_SEQUENCE_H_

#include "CsObject.h"
#include "CsVector.h"

class CS_API CsCoordinateSequence
{
public:
	CsCoordinateSequence();

private:
	CsVector<cs_real> m_tCoords;
};

#endif // _GEOMETRY_COORDINATE_SEQUENCE_H_