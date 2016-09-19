#ifndef _CSCORE_CSOBJECT_H_
#define _CSCORE_CSOBJECT_H_

#include "CsCoreGlobal.h"

class CsObject_Private;
class CsString;
class CsBytes;

class CS_CORE_EXPORT CsObject
{
public:
	CsObject();
	CsObject(CsObject_Private *pPrivate);
	virtual ~CsObject() = 0;

	virtual CsObject *CopyToObject() const;
	virtual cs_uint ClassCode() const;
	virtual CsString ToString() const;
	virtual cs_uint64 HashCode() const;
	virtual cs_bool Serialize(CsBytes &tBytes) const;
	virtual cs_bool Deserialize(const CsBytes &tBytes);

protected:
	CS_DECLARE_PRIVATE(CsObject);

public:
	enum { CLASSCODE = CORE_CLASSCODE_OBJECT, };
};

#endif // _CSCORE_CSOBJECT_H_
