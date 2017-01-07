#ifndef _CORE_UNSIGNED_CHARACTER_H_
#define _CORE_UNSIGNED_CHARACTER_H_

#include "gpackage.h"

class GAPI CsUnsignedCharacter 
	: public GNumber<guchar>
{
public:
	enum { CLASS_CODE = CLASS_CODE_UNSIGNED_CHARACTER, };

public:
	CsUnsignedCharacter(guchar val = '\0');
	CsUnsignedCharacter(const CsUnsignedCharacter &);
	virtual guint ClassCode() const;
};

typedef CsUnsignedCharacter CsUCharacter;
typedef CsUnsignedCharacter CsUnsignedChar;
typedef CsUnsignedCharacter CsUChar;

#endif // _CORE_UNSIGNED_CHARACTER_H_