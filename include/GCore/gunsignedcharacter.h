#ifndef _CORE_UNSIGNED_CHARACTER_H_
#define _CORE_UNSIGNED_CHARACTER_H_

#include "gpackage.h"

namespace gnova { // gnova

class GAPI GUnsignedCharacter 
	: public GNumber<guchar>
{
public:
	enum { CLASS_CODE = CLASS_CODE_UNSIGNED_CHARACTER, };

public:
	GUnsignedCharacter(guchar val = '\0');
	GUnsignedCharacter(const GUnsignedCharacter &);
	virtual guint ClassCode() const;
};

typedef GUnsignedCharacter GUCharacter;
typedef GUnsignedCharacter GUnsignedChar;
typedef GUnsignedCharacter GUChar;

} // namespace gnova

#endif // _CORE_UNSIGNED_CHARACTER_H_