#include "CsJsonObject.h"
#include "CsString.h"

CsJsonObject::CsJsonObject()
: m_bValid(true)
{

}

CsJsonObject::CsJsonObject(const CsString &jsonStr)
: m_bValid(true)
{
	Parse(jsonStr);
}

CsJsonObject::CsJsonObject(const CsJsonObject &jsonObj)
{

}

CsJsonObject::~CsJsonObject()
{

}

cs_bool CsJsonObject::Parse(const CsString &jsonStr, cs_size_t cursor)
{
	if (jsonStr.IsEmpty())
	{
		return false;
	}

	return true;
}
