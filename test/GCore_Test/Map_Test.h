//#include "CsMap.h"
#include "gglobal.h"
#include "gordermap.h"
#include "gstring.h"
#include <iostream>

gvoid TestMap()
{
	GOrderMap<gint, GString> map;

	map.Insert(1, "1");
	map.Insert(2, "2");
	map.Insert(-10, "-10");
	map.Insert(5, "5");
	map.Insert(5, "100");
	map[6] = "6";

	GOrderMap<gint, GString>::ConstIterator _citer = map.ConstFind(-10);
	std::cout << _citer.Key() << " " << _citer.Value().CString() << std::endl;

	GOrderMap<gint, GString> _map;
	_map = map;
	std::cout << "size: " << _map.Size() << std::endl;
	for (GOrderMap<gint, GString>::ConstIterator citer = _map.ConstBegin();
		citer != _map.ConstEnd(); citer++)
	{
		std::cout << citer.Key() << " " << citer.Value().CString() << std::endl;
	}

	int stop = 1;
	stop++;

}