#ifndef _CORE_GLOBAL_H_
#define _CORE_GLOBAL_H_

#include "gtype.h"

namespace gsystem {

	class GString8;
	class GString16;
	class GString32;
	

#ifdef G_CHAR_BYTE_8
	typedef GString8		GString;
	typedef	gchar8 *		gstring;
	typedef	const gchar8 *	gcstring;
#endif

	template <typename StringT> class GStringListT;
	typedef GStringListT<GString> GStringList;
}

#endif // _CORE_GLOBAL_H_