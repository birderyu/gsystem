#include "CsOrderSet.h"
#include <iostream>

cs_void SetTest()
{
	CsOrderSet<cs_int> set;
	set.Insert(1);
	set.Insert(2);
	set.Insert(-10);
	set.Insert(5);
	set.Insert(5);

	CsOrderSet<cs_int> _set;
	_set = set;
	std::cout << "size: " << _set.Size() << std::endl;
	for (CsOrderSet<cs_int>::ConstIterator citer = _set.ConstBegin();
		citer != _set.ConstEnd(); citer++)
	{
		std::cout << *citer << std::endl;
	}

	int stop = 1;
	stop++;
}