#ifndef _CSCORE_CSOBJECT_H_
#define _CSCORE_CSOBJECT_H_

#include "CsCoreGlobal.h"

class CsObject_Private;
class CsString;

class CsCore_Export CsObject
{
public:
	CsObject();
	CsObject(CsObject_Private *pPrivate);
	virtual ~CsObject() = 0;

	virtual CsObject *CopyToObject() const;
	virtual cs_uint ClassCode() const;
	virtual CsString ToString() const;
	virtual cs_bool Equals(CsObject *pObject) const;
	virtual cs_uint64 HashCode() const;

protected:
	CS_DECLARE_PRIVATE(CsObject);

public:
	enum { CLASSCODE = CORE_CLASSCODE_OBJECT, };
};

#endif // _CSCORE_CSOBJECT_H_
