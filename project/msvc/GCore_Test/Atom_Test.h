#include "gatom.h"

gvoid AtomTest()
{
	gsize var = 100;
	gsize var2 = 1000;
	gsize var3 = 10;
	gsize var4 = GAtom::ValuedCompareAndSwap(&var, var3, var2);

	gint stop = 1;
	stop++;
}
