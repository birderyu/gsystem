#ifndef _CORE_GEOMETRY_FACTORY_H_
#define _CORE_GEOMETRY_FACTORY_H_

#include "CsGeometry.h"
#include "CsSingleton.h"

class CS_API CsGeometryFactory 
	: public CsSingleton<CsGeometryFactory, CsMutex>
{

};

#endif // _CORE_GEOMETRY_FACTORY_H_