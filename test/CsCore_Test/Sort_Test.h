#include "gsort.h"
#include "gdynamicarray.h"

template<class T>
struct CsMore
	: public GBinaryF<T, T, gbool>
{
	gbool operator()(const T &left, const T &right) const
	{
		return (left > right);
	}
};

gvoid TestSort()
{
	GDynamicArray<gint> arr(5);
	arr[0] = 5;
	arr[1] = 3;
	arr[2] = 9;
	arr[3] = 8;
	arr[4] = 1;
	GSort::QuickSort<GDynamicArray<gint>, gint>(arr, 1, arr.Size() - 2);
	for (gsize i = 0; i < arr.Size(); i++)
	{
		std::cout << arr[i] << std::endl;
	}
	
	int stop = 1;
	stop++;
}