#ifndef _CORE_SIGNED_CHARACTER_H_
#define _CORE_SIGNED_CHARACTER_H_

#include "CsPackage.h"

class CS_API CsSignedCharacter 
	: public CsPackage<cs_schar>
{
public:
	enum { CLASS_CODE = CLASS_CODE_SIGNED_CHARACTER, };

public:
	CsSignedCharacter(cs_schar val = '\0');
	CsSignedCharacter(const CsSignedCharacter &);
	virtual ~CsSignedCharacter();

	virtual cs_uint ClassCode() const;
};

typedef CsSignedCharacter CsSCharacter;
typedef CsSignedCharacter CsSignedChar;
typedef CsSignedCharacter CsSChar;

#endif // _CORE_SIGNED_CHARACTER_H_