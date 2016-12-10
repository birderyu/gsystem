#ifndef _CORE_BYTE_H_
#define _CORE_BYTE_H_

#include "CsPackage.h"

class CS_API CsByte 
	: public CsPackage<cs_byte>
{
public:
	enum { CLASSCODE = CORE_CLASSCODE_BYTE, };

public:
	CsByte(cs_byte val = 0);
	CsByte(const CsByte &);

	cs_uint ClassCode() const;
};

#endif // _CORE_BYTE_H_