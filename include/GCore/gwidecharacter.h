#ifndef _CORE_WIND_CHARACTER_H_
#define _CORE_WIND_CHARACTER_H_

#include "gpackage.h"

namespace gsystem { // gsystem

class GAPI GWideCharacter 
	: public GPackage<gwchar>
{
public:
	GWideCharacter(gwchar val);
	GWideCharacter(const GWideCharacter &);

	guint ClassCode() const;
};

typedef GWideCharacter GWCharacter;
typedef GWideCharacter GWindChar;
typedef GWideCharacter GWChar;

} // namespace gsystem

#endif // _CORE_WIND_CHARACTER_H_