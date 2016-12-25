#ifndef _CORE_JSON_VALUE_H_
#define _CORE_JSON_VALUE_H_

#include "CsJsonObject.h"
#include "CsVariant.h"

class CS_API CsJsonValue
	: public CsJsonObject
{
public:
	CsJsonValue();
	CsJsonValue(const CsString &);
	CsJsonValue(const CsJsonValue &);

private:
	CsString m_sKey;
	CsVariant m_tValue;
};

#endif // _CORE_JSON_VALUE_H_