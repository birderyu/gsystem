#ifndef _CORE_JSON_ARRAY_H_
#define _CORE_JSON_ARRAY_H_

#include "CsJsonObject.h"
#include "CsList.h"
#include "CsVariant.h"

typedef CsList<CsVariant> CsVariantList;

class CS_API CsJsonArray
	: public CsJsonObject
{
public:
	CsJsonArray();
	CsJsonArray(const CsString &);
	CsJsonArray(const CsVariantList &);
	CsJsonArray(const CsJsonArray &);

private:
	CsString m_sKey;
	CsVariantList m_tValue;
};

#endif // _CORE_JSON_ARRAY_H_