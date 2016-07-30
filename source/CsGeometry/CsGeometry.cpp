#include "CsGeometry.h"
#include "CsGeometry_Private.h"

CsGeometry::CsGeometry()
:CsObject(new CsGeometry_Private(this))
{

}

CsGeometry::~CsGeometry()
{

}