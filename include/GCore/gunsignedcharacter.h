#ifndef _CORE_UNSIGNED_CHARACTER_H_
#define _CORE_UNSIGNED_CHARACTER_H_

#include "gpackage.h"

namespace gsystem { // gsystem

class GAPI GUnsignedCharacter 
	: public GNumber<guchar>
{
public:
	GUnsignedCharacter(guchar val = '\0');
	GUnsignedCharacter(const GUnsignedCharacter &);
	virtual guint ClassCode() const;
};

typedef GUnsignedCharacter GUCharacter;
typedef GUnsignedCharacter GUnsignedChar;
typedef GUnsignedCharacter GUChar;

} // namespace gsystem

#endif // _CORE_UNSIGNED_CHARACTER_H_