#include "gstring.h"
#include <iostream>
#include "BTree_Test.h"
#include "Sort_Test.h"
#include "MemPool_Test.h"


#include "gstringlist.h"
#include "gvariety.h"
#include "gmemorypool.h"
#include "gpackage.h"
#include "Bytes_Test.h"
#include "gsinglelinkedlist.h"
#include "gmutex.h"
#include "gvoidlock.h"
#include "gnew.h"

#include "gblock.h"
#include "gcstringhelper.h"
#include "List_Test.h"
#include "gnumber.h"
#include "Hash_Test.h"

#include "gsharedpointer.h"

#include "gstringlist.h"
#include "gstaticarray.h"
#include "gsingleton.h"
#include "gbinaryheap.h"

#include "Array_Test.h"
#include "Vector_Test.h"
#include "File_Test.h"
#include "Map_Test.h"
#include "Set_Test.h"

#include "json_test.h"
#include "gcriticalsection.h"
#include "guniquepointer.h"

#include "Atom_Test.h"
#include "Traits_Test.h"

#include "gallocator.h"
#include "gconstructor.h"
#include "gseries.h"
#include "gbytes.h"
#include "gvariety.h"
#include "gvariant_example.h"

#include "variant.h"

#include "gmemorypool_example.h"
#include "garray_example.h"
#include <time.h>
#include "gstopwatch.h"

#include "gthread_example.h"

#include "gtuple_example.h"
#include "gdatetime_example.h"
#include "gtable_example.h"

int main(int argc, char *argv[])
{
	Table_Test();
	Tuple_Test();
	Time_Test();

	GDateTime dt = GDateTime::Now();
	GString sdt = dt.ToString();

	system("pause");
}