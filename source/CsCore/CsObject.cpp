#include "CsObject.h"
#include "CsObject_Private.h"
#include "CsString.h"

CsObject::CsObject(CsObject_Private *pPrivate)
: m_pPrivate(pPrivate)
{
	
}

CsObject::~CsObject()
{
	if (m_pPrivate)
	{
		delete m_pPrivate;
	}
}

CsString CsObject::ToString() const
{
	return "CsObject";
}

CsObject *CsObject::CopyToObject() const
{
	return NULL;
}

cs_uint CsObject::ClassCode() const
{
	return CsObject::CLASSCODE;
}

cs_bool CsObject::Equals(CsObject *pObject) const
{
	return this == pObject;
}

cs_uint64 CsObject::HashCode() const
{
	return (cs_uint64)this;
}