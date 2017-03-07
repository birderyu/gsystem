#pragma once

#include "gdatetime.h"
#include "gdate.h"
#include "gtime.h"

gvoid Time_Test()
{
	GTime t = GTime::Now();
	GTime t2(t);

	t2.AddHours(-1);

	printf("%d ±%d∑÷%d√Î%d∫¡√Î\n",
		t2.Hour(),
		t2.Minute(),
		t2.Second(),
		t2.Millisecond());
}