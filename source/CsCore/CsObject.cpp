#include "CsObject.h"
#include "CsObject_Private.h"
#include "CsString.h"

CsObject::CsObject()
: m_pPrivate(NULL)
{

}

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

cs_uint64 CsObject::HashCode() const
{
	return (cs_uint64)this;
}

cs_bool CsObject::Serialize(CsBytes &tBytes) const
{
	return false;
}

cs_bool CsObject::Deserialize(const CsBytes &tBytes)
{
	return false;
}