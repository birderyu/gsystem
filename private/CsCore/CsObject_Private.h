#ifndef _CSCORE_CSOBJECT_PRIVATE_H_
#define _CSCORE_CSOBJECT_PRIVATE_H_

#include "CsGlobal.h"

class CsObject;

class CsObject_Private
{
public:
	CsObject_Private(CsObject *pPublic)
		:m_pPublic(pPublic)
	{

	}

	virtual ~CsObject_Private()
	{

	}
	
protected:
	CS_DECLARE_PUBLIC(CsObject);
};

#endif // _CSCORE_CSOBJECT_PRIVATE_H_