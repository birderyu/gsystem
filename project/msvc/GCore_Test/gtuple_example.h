#pragma once

#include "gtuple.h"
#include "gstring.h"

gvoid Pari_Test()
{
	GPair<gint, GString> pair = GMakePair(1, GString("abc"));
	GPair<gint, GString>::FirstType v1 = pair.First();
	GPair<gint, GString>::SecondType v2 = pair.Second();
}

gvoid Tuple_Test()
{
	GTuple<gint, gdouble, GString, gint> tuple = GMakeTuple<gint, gdouble, GString>(1, 1.1, GString("abcdefghij"), 10);
	
	GTupleSet<0>(tuple, 10);
	GTupleSet<1>(tuple, 10.1);
	GTupleSet<2>(tuple, GString("birderyu"));
	
	gint v1 = GTupleGet<0>(tuple);
	gdouble v2 = GTupleGet<1>(tuple);
	GString v3 = GTupleGet<2>(tuple);

	tuple.SetAt<gint>(0, 2);
	tuple.SetAt<gdouble>(1, 2.2);
	tuple.SetAt<GString>(2, GString("xyz"));

	gint vv1 = tuple.GetAt<gint>(0);
	gdouble vv2 = tuple.GetAt<gdouble>(1);
	GString vv3 = tuple.GetAt<GString>(2);

	gint stop = 1;
	stop++;
}
