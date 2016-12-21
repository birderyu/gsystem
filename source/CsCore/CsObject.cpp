#include "CsObject.h"
#include "CsString.h"

CsObject::~CsObject()
{

}

CsObjectP CsObject::Clone() const
{
	return CsObjectP();
}

const CsObject *CsObject::Boxing() const
{
	return this;
}

cs_bool CsObject::Unboxing(const CsObject *)
{
	return false;
}

CsString CsObject::ToString() const
{
	return "This is an object.";
}

cs_uint CsObject::ClassCode() const
{
	return CsObject::ClassCode();
}

cs_uint CsObject::HashCode() const
{
	return 0;
}

cs_bool CsObject::Equals(const CsObject *) const
{
	return false;
}

cs_bool CsObject::Serializable() const
{
	return false;
}
