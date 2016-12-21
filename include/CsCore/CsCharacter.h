#ifndef _CORE_CHARACTER_H_
#define _CORE_CHARACTER_H_

#include "CsPackage.h"

class CS_API CsCharacter 
	: public CsPackage<cs_char>
{
public:
	enum { CLASS_CODE = CLASS_CODE_CHARACTER, };

public:
	CsCharacter(cs_char val = '\0');
	CsCharacter(const CsCharacter &);

	cs_uint ClassCode() const;
};

typedef CsCharacter CsChar;

#endif // _CORE_CHARACTER_H_