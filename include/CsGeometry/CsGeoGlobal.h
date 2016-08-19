#ifndef _CSGEO_CSGEOGLOBAL_H_
#define _CSGEO_CSGEOGLOBAL_H_

#include "CsCore/CsGlobal.h"

#  if defined (CS_GEO_BUILD_DLL)
#    define CsGeo_Export CS_DECL_EXPORT
#  else 
#    define CsGeo_Export CS_DECL_IMPORT
#  endif  

//#define CS_GEO_HAS_Z

enum EM_GEO_CLASSCODE
{
	GEO_CLASSCODE_GEOMETRY = 1000,
	GEO_CLASSCODE_ENVELOPE,
	GEO_CLASSCODE_POINT,
};

enum EM_GEO_TYPE
{
	GEO_TYPE_UNKNOWN,
};

#endif // _CSGEO_CSGEOGLOBAL_H_