#include "gorderset.h"
#include <iostream>

gvoid SetTest()
{
	GOrderSet<gint> set;
	set.Insert(1);
	set.Insert(2);
	set.Insert(-10);
	set.Insert(5);
	set.Insert(5);

	GOrderSet<gint> _set;
	_set = set;
	std::cout << "size: " << _set.Size() << std::endl;
	for (GOrderSet<gint>::ConstIterator citer = _set.ConstBegin();
		citer != _set.ConstEnd(); citer++)
	{
		std::cout << *citer << std::endl;
	}

	int stop = 1;
	stop++;
}