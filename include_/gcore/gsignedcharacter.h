#ifndef _CORE_SIGNED_CHARACTER_H_
#define _CORE_SIGNED_CHARACTER_H_

#include "gpackage.h"

namespace gsystem { // gsystem

class GAPI GSignedCharacter 
	: public GPackage<gschar>
{
public:
	GSignedCharacter(gschar val = '\0');
	GSignedCharacter(const GSignedCharacter &);
	virtual ~GSignedCharacter();

	virtual guint ClassCode() const GNOEXCEPT;
};

typedef GSignedCharacter GSCharacter;
typedef GSignedCharacter GSignedChar;
typedef GSignedCharacter GSChar;

} // namespace gsystem

#endif // _CORE_SIGNED_CHARACTER_H_