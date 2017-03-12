#ifndef _CORE_CHARACTER_H_
#define _CORE_CHARACTER_H_

#include "gpackage.h"

namespace gnova { // gnova

class GAPI GCharacter 
	: public GPackage<gchar>
{
public:
	enum { CLASS_CODE = CLASS_CODE_CHARACTER, };

public:
	GCharacter(gchar val = '\0');
	GCharacter(const GCharacter &);

	guint ClassCode() const;
};

typedef GCharacter GChar;

} // namespace gnova

#endif // _CORE_CHARACTER_H_