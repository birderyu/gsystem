//#include "CsMap.h"
#include "CsGlobal.h"
#include "CsOrderMap.h"
#include "CsString.h"
#include <iostream>

cs_void TestMap()
{
	CsOrderMap<cs_int, CsString> map;

	map.Insert(1, "1");
	map.Insert(2, "2");
	map.Insert(-10, "-10");
	map.Insert(5, "5");
	map.Insert(5, "100");
	map[6] = "6";

	CsOrderMap<cs_int, CsString>::ConstIterator _citer = map.ConstFind(-10);
	std::cout << _citer.Key() << " " << _citer.Value().CString() << std::endl;

	CsOrderMap<cs_int, CsString> _map;
	_map = map;
	std::cout << "size: " << _map.Size() << std::endl;
	for (CsOrderMap<cs_int, CsString>::ConstIterator citer = _map.ConstBegin();
		citer != _map.ConstEnd(); citer++)
	{
		std::cout << citer.Key() << " " << citer.Value().CString() << std::endl;
	}

	int stop = 1;
	stop++;

}