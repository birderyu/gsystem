#ifndef _CSGEO_CSGEOGLOBAL_H_
#define _CSGEO_CSGEOGLOBAL_H_

#include "CsCore/CsGlobal.h"

#  if defined (CS_GEO_BUILD_DLL)
#    define CsGeo_Export CS_DECL_EXPORT
#  else 
#    define CsGeo_Export CS_DECL_IMPORT
#  endif  

enum EM_GEO_CLASSCODE
{
	GEO_CLASSCODE_GEOMETRY = 1001,
	GEO_CLASSCODE_ENVELOPE = 1001,
	GEO_CLASSCODE_POINT,
};

#endif // _CSGEO_CSGEOGLOBAL_H_