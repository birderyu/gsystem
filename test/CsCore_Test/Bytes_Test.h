#include "CsBytes.h"
#include "CsString.h"

cs_void TestBytes()
{
	CsBytes bytes;
	cs_uint64 a = 111, _a;
	cs_uint64 b = 222, _b;
	cs_uint64 c = 333, _c;
	cs_uint64 d = 444, _d;
	CsString e = "123";
	CsString _e;
	bytes << a << b << c << d;
	bytes >> _a >> _b >> _c >> _d;

	cs_size_t size = bytes.Size();

	int stop = 1;
	stop++;
}