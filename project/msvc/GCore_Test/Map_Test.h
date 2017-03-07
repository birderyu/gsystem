#include "gmap.h"
#include "gglobal.h"
#include "gordermap.h"
#include "gunordermap.h"
#include "gstring.h"
#include <iostream>

gvoid TestMap()
{
	GMap<gint, GString> map;

	map.Insert(1, "1");
	map.Insert(2, "2");
	map.Insert(-10, "-10");
	map.Insert(5, "5");
	map.Insert(5, "100");

	GMap<gint, GString>::ConstIterator _citer = map.ConstFind(-10);
	std::cout << _citer.Key() << " " << _citer.Value().CString() << std::endl;

	GMap<gint, GString> _map;
	_map = map;
	std::cout << "size: " << _map.Size() << std::endl;

	/*
	for (GMap<gint, GString>::Iterator iter = _map.Begin();
		iter != _map.End();)
	{
		if (iter.Key() == 1)
		{
			_map.Erase(iter++);
		}
		else
		{
			iter++;
		}
	}
	*/
	_map.Remove(1);
	for (GMap<gint, GString>::ConstIterator citer = _map.ConstBegin();
		citer != _map.ConstEnd(); citer++)
	{
		std::cout << citer.Key() << " " << citer.Value().CString() << std::endl;
	}

	int stop = 1;
	stop++;

}