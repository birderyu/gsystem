#ifndef _GEOMETRY_LINE_STRING_H_
#define _GEOMETRY_LINE_STRING_H_

#include "ggeometry.h"
#include "gpoint.h"

namespace gsystem { // gsystem
namespace geom { // gsystem.geom

class GAPI GLineString
{
public:
	virtual greal Length() const = 0;
	virtual GPointPtr StartPoint() const = 0;
	virtual GPointPtr EndPoint() const = 0;

	virtual gsize PointCount() const = 0;
	virtual GPointPtr GetPointAt(gsize pos) const = 0;
	virtual gvoid SetPointAt(gsize pos, const GPointPtr &poi) = 0;

	// ÊÇ·ñ±ÕºÏ
	virtual gbool IsClosed() const = 0;
};

}
}

#endif // _GEOMETRY_LINESTRING_H_
