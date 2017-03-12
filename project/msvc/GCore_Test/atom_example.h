#include "gatom.h"

gnova::gvoid AtomTest()
{
	gnova::gsize var = 100;
	gnova::gsize var2 = 1000;
	gnova::gsize var3 = 10;
	gnova::gsize var4 = gnova::GAtom::ValuedCompareAndSwap(&var, var3, var2);
}
