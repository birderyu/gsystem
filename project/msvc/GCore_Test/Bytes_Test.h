#include "gbytes.h"
#include "gstring.h"

gvoid TestBytes()
{
	GBytes bytes;
	guint64 a = 111, _a;
	guint64 b = 222, _b;
	guint64 c = 333, _c;
	guint64 d = 444, _d;
	GString e = "123";
	GString _e;
	/*
	bytes << a << b << c << d;
	bytes >> _a >> _b >> _c >> _d;
	*/

	gsize size = bytes.Size();

	int stop = 1;
	stop++;
}