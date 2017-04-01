#ifndef _GEOMETRY_GEOMETRY_HELPER_H_
#define _GEOMETRY_GEOMETRY_HELPER_H_

#include "ggeometryinterface.h"

namespace gsystem { // gsystem
namespace geom { // gsystem.geom

class GAPI GGeometryHelper
{
public:
	template<typename GeometryT> static GSharedPointer<GeometryT> ConvertTo(GGeometryPtr &geo);
	template<typename GeometryT> static GSharedPointer<GeometryT> ConvertTo(GPointPtr &point);
};

}
}

#include "ggeometryhelper.inl"

#endif // _GEOMETRY_GEOMETRY_HELPER_H_