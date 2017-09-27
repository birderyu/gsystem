#ifndef _CORE_STRING_H_
#define _CORE_STRING_H_

#include "gtype.h"

namespace gsystem {

	class GString8;
	typedef GString8		GString;
	typedef	gchar8 *		gstring;
	typedef	const gchar8 *	gcstring;
	template <typename StringT> class GStringListT;
	typedef GStringListT<GString> GStringList;

	/*
#ifdef G_CHAR_BYTE_8
	typedef GString8		GString;
	typedef	gchar8 *		gstring;
	typedef	const gchar8 *	gcstring;
#endif
	*/

	//template <typename StringT> class GStringListT;
	//typedef GStringListT<GString> GStringList;
}



#endif // _CORE_STRING_H_