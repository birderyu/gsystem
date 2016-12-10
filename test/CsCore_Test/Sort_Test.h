#include "CsSort.h"
#include "CsDynamicArray.h"

template<class T>
struct CsMore
	: public CsBinaryF<T, T, cs_bool>
{
	cs_bool operator()(const T &left, const T &right) const
	{
		return (left > right);
	}
};

cs_void TestSort()
{
	CsDynamicArray<cs_int> arr(5);
	arr[0] = 5;
	arr[1] = 3;
	arr[2] = 9;
	arr[3] = 8;
	arr[4] = 1;
	CsSort::QuickSort<CsDynamicArray<cs_int>, cs_int>(arr, 1, arr.Size() - 2);
	for (cs_size_t i = 0; i < arr.Size(); i++)
	{
		std::cout << arr[i] << std::endl;
	}
	
	int stop = 1;
	stop++;
}