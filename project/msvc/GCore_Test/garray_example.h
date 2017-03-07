#pragma once
#include <iostream>
#include "gdynamicarray.h"
#include "gstaticarray.h"
#include "gstring.h"

gvoid DynamicArray_Test1()
{
	gsize arr_size = 100;
	GDynamicArray<gint> arr(arr_size);
}

gvoid DynamicArray_Test()
{
	gsize arr_size = 100;
	GDynamicArray<GString> arr(arr_size);
	for (gsize i = 0; i < arr.Size(); i++)
	{
		arr[i] = GString::Number(i + 1);
	}
	for (gsize i = 0; i < arr.Size(); i++)
	{
		std::cout << arr[i].CString() << std::endl;
	}

	gint stop = 1;
	stop++;
}