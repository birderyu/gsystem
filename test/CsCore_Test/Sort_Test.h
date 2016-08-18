#include "CsSort.h"
#include "CsArray.h"

template<class T>
struct CsMore
	: public CsBinaryF<T, T, cs_bool>
{
	cs_bool operator()(const T &left, const T &right) const
	{
		return (left > right);
	}
};

void TestInsertSort()
{
	CsArray<cs_int> arr(10);
	arr[0] = 5;
	arr[1] = 3;
	arr[2] = 9;
	arr[3] = 8;
	arr[4] = 1;
	arr[5] = 1200;
	arr[6] = -51;
	arr[7] = 12;
	arr[8] = 4;
	arr[9] = 2;
	CsSort::QuickSort<CsArray<cs_int>, cs_int>(arr/*, 0*/, arr.Length());
	for (cs_size_t i = 0; i < arr.Length(); i++)
	{
		std::cout << arr[i] << std::endl;
	}
	
	int stop = 1;
	stop++;
}