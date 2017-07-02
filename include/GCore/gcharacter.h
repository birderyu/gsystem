#ifndef _CORE_CHARACTER_H_
#define _CORE_CHARACTER_H_

#include "gpackage.h"

namespace gsystem { // gsystem

	class GAPI GCharacter
		: public GPackage<gchar>
	{
	public:
		GCharacter(gchar val = '\0');
		GCharacter(const GCharacter &);

		guint ClassCode() const GNOEXCEPT;
	};

	typedef GCharacter GChar;

} // namespace gsystem

#endif // _CORE_CHARACTER_H_