#include "gbytes.h"
#include "gstring.h"

gnova::gvoid TestBytes()
{
	gnova::GBytes bytes;
	gnova::guint64 a = 111, _a;
	gnova::guint64 b = 222, _b;
	gnova::guint64 c = 333, _c;
	gnova::guint64 d = 444, _d;
	gnova::GString e = "123";
	gnova::GString _e;
	/*
	bytes << a << b << c << d;
	bytes >> _a >> _b >> _c >> _d;
	*/

	gnova::gsize size = bytes.Size();
}