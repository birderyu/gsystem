#include "typedef_test.h"
#include "binaryheap_test.h"
#include "ghuffmantree.h"

using namespace gsystem;

gint main(gint argc, gchar *argv[])
{
	GHuffmanTree<gbyte> huffmanTree;

	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
}