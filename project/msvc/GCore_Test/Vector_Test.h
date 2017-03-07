#include "gvector.h"

gvoid TestVector()
{
	GVector<gint> arr(5);
	arr.Reserve(10);
	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;
	arr[3] = 4;
	arr[4] = 5;

	arr.PushBack(6);
	arr.PushFront(0);

	GVector<gint> _arr(arr);
	_arr.Append(7);
	_arr.PopFront();
	_arr.PopFront();
	_arr.PopBack();
	

	gint first = _arr.First();
	gint last = _arr.Last();

	gbool b1 = _arr.StartWith(0);
	gbool b2 = _arr.EndWith(7);

	GVector<gint> __arr(_arr);
	for (GVector<gint>::ConstIterator citer = __arr.ConstBegin();
		citer != __arr.ConstEnd(); citer++)
	{
		std::cout << *citer << std::endl;
	}
	std::cout << std::endl;
	
	gint stop = 1;
	stop++;
}