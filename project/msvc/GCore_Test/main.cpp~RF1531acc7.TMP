#include "typedef_test.h"
#include "binaryheap_test.h"
#include "ghuffmantree.h"
#include "gmap.h"
#include "gbkcode.h"
#include "gstopwatch.h"
#include <fstream>

using namespace gsystem;

struct ByteCounter
{
	guint16 key;
	gsize count;
};

gbool operator<(const ByteCounter &bc1, const ByteCounter &bc2)
{
	if (bc1.count < bc2.count)
	{
		return true;
	}
	else if (bc1.count > bc2.count)
	{
		return false;
	}
	return bc1.key < bc2.key;
}

ByteCounter operator+(const ByteCounter &bc1, const ByteCounter &bc2)
{
	ByteCounter bc;
	bc.key = bc1.key + bc2.key;
	bc.count = bc1.count + bc2.count;
	return bc;
}

gvoid sec(gbyte n, std::ofstream &fs)
{
	gbyte bin[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	gint total = 7;
	guint i = 0, j = 0;
	while (n != 0)
	{
		i = n / 2;
		j = n % 2;
		n = n / 2;
		bin[total--] = j;
	}
	for (gsize i = 0; i < 8; i++)
	{
		fs << (gint)bin[i];
	}
}

gvoid getHuffmanCode(const GHuffmanTreeNode<ByteCounter> &node)
{
	
}

gsize g_strlen(gcstring str)
{
	gsize i = 0;
	while (str[i++]) {}
	return i - 1;
}

gint main(gint argc, gchar *argv[])
{
	gcstring c_str = "123456789";
	gsize iiiii = ::strlen(NULL);

	GStopWatch _sw;
	_sw.Start();
	for (gsize i = 0; i < 10000000; i++)
	{
		g_strlen(c_str);
	}
	gsize time1 = _sw.Stop();
	for (gsize i = 0; i < 10000000; i++)
	{
		::strlen(c_str);
	}
	gsize time2 = _sw.Stop();

	std::ofstream ofile1("C:\\Users\\Birderyu\\Desktop\\before.txt"), ofile2("C:\\Users\\Birderyu\\Desktop\\after.txt");
	std::cout << "压缩前为：" << 41804 * 8 << "bit" << std::endl;

	for (gsize i = 0; i < 41804; i++)
	{
		sec(gbk_bytes[i], ofile1);
	}
	ofile1.close();

	GStopWatch sw;
	sw.Start();
	std::cout << "统计频率：" << std::endl;
	GMap<gbyte, ByteCounter> map;
	for (gsize i = 0; i < 41804; i++)
	{
		if (map.Contains(gbk_bytes[i]))
		{
			map.Find(gbk_bytes[i]).Value().count++;
		}
		else
		{
			ByteCounter bc;
			bc.count = 1;
			bc.key = (guint16)gbk_bytes[i];
			map.Insert(gbk_bytes[i], bc);
		}
	}
	GDynamicArray<ByteCounter> bcs(map.Size());
	gsize index = 0;
	for (GMap<gbyte, ByteCounter>::ConstIterator iter = map.ConstBegin();
		iter != map.ConstEnd(); iter++)
	{
		bcs[index++] = iter.Value();
		std::cout
			<< (gint)iter.Key()
			<< "出现了"
			<< iter.Value().count
			<< "次，其值为："
			<< iter.Value().key
			<< std::endl;
	}
	std::cout << "统计频率完成，共用时：" << sw.Stop() << "毫秒" << std::endl;


	std::cout << "构建哈夫曼树：" << std::endl;
	GHuffmanTree<ByteCounter> huffmanTree;
	huffmanTree.Append(bcs, 0, bcs.Size());
	GDynamicArray<gbyte> code;
	GMap<gbyte, GDynamicArray<gbyte>> code_map;


	std::cout << "哈夫曼树构建完成，共用时：" << sw.Stop() << "毫秒" << std::endl;




	std::cout << "压缩后为：" << std::endl;


	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
}