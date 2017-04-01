#pragma once
#include <gtest/gtest.h>
#include "gseries.h"

TEST(SeriesTest, HandleNoneZeroInput)
{
	using namespace gsystem;
	using GSeriesT = GSeries<gchar, 8, true, '\0'>;

	gcstring str = "abc";
	GSeriesT ser = GSeriesT::ReferenceOf(str, 3);
	ser[4] = 'd';

	ser.Resize(20);

	gint stop = 1;
	stop++;
}