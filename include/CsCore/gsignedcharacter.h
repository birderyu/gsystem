#ifndef _CORE_SIGNED_CHARACTER_H_
#define _CORE_SIGNED_CHARACTER_H_

#include "gpackage.h"

class GAPI GSignedCharacter 
	: public GPackage<gschar>
{
public:
	enum { CLASS_CODE = CLASS_CODE_SIGNED_CHARACTER, };

public:
	GSignedCharacter(gschar val = '\0');
	GSignedCharacter(const GSignedCharacter &);
	virtual ~GSignedCharacter();

	virtual guint ClassCode() const;
};

typedef GSignedCharacter GSCharacter;
typedef GSignedCharacter GSignedChar;
typedef GSignedCharacter GSChar;

#endif // _CORE_SIGNED_CHARACTER_H_