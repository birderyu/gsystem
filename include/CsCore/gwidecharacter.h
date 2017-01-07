#ifndef _CORE_WIND_CHARACTER_H_
#define _CORE_WIND_CHARACTER_H_

#include "gpackage.h"

class GAPI GWideCharacter 
	: public GPackage<gwchar>
{
public:
	enum { CLASS_CODE = CLASS_CODE_WIND_CHARACTER, };

public:
	GWideCharacter(gwchar val);
	GWideCharacter(const GWideCharacter &);

	guint ClassCode() const;
};

typedef GWideCharacter GWCharacter;
typedef GWideCharacter GWindChar;
typedef GWideCharacter GWChar;

#endif // _CORE_WIND_CHARACTER_H_