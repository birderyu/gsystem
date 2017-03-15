#include <iostream>
#include "gtable_example.h"
#include "gconstructor_example.h"

using namespace gsystem;

gint main(gint argc, gchar *argv[])
{
	Constructor_Test();
	Table_Test();
	system("pause");
}