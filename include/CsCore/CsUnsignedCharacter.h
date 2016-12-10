#ifndef _CORE_UNSIGNED_CHARACTER_H_
#define _CORE_UNSIGNED_CHARACTER_H_

#include "CsPackage.h"

class CS_API CsUnsignedCharacter 
	: public CsNumber<cs_uchar>
{
public:
	enum { CLASSCODE = CORE_CLASSCODE_UNSIGNED_CHARACTER, };

public:
	CsUnsignedCharacter(cs_uchar val = '\0');
	CsUnsignedCharacter(const CsUnsignedCharacter &);
	virtual cs_uint ClassCode() const;
};

typedef CsUnsignedCharacter CsUCharacter;
typedef CsUnsignedCharacter CsUnsignedChar;
typedef CsUnsignedCharacter CsUChar;

#endif // _CORE_UNSIGNED_CHARACTER_H_