#include "gdynamicarray.h"

gvoid TestDynamicArray()
{
	GDynamicArray<gint> arr(5);
	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;
	arr[3] = 4;
	arr[4] = 5;

	for (gsize i = 0; i < arr.Size(); i++)
	{
		std::cout << i << ": " << arr[i] << std::endl;
	}
	std::cout << std::endl;

	arr.Resize(10, 1, 3, 8, -99999);

	for (gsize i = 0; i < arr.Size(); i++)
	{
		std::cout << i << ": " << arr[i] << std::endl;
	}

	gint stop = 1;
	stop++;
}