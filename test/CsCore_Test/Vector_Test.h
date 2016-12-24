#include "CsVector.h"

cs_void TestVector()
{
	CsVector<cs_int> arr(5);
	arr.Reserve(10);
	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;
	arr[3] = 4;
	arr[4] = 5;

	arr.PushBack(6);
	arr.PushFront(0);

	CsVector<cs_int> _arr(arr);
	_arr.Append(7);
	_arr.PopFront();
	_arr.PopFront();
	_arr.PopBack();
	

	cs_int first = _arr.First();
	cs_int last = _arr.Last();

	cs_bool b1 = _arr.StartWith(0);
	cs_bool b2 = _arr.EndWith(7);

	CsVector<cs_int> __arr(_arr);
	for (CsVector<cs_int>::ConstIterator citer = __arr.ConstBegin();
		citer != __arr.ConstEnd(); citer++)
	{
		std::cout << *citer << std::endl;
	}
	std::cout << std::endl;
	
	cs_int stop = 1;
	stop++;
}