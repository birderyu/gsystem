#pragma once

#include "gtable.h"
#include "gstring.h"

gnova::gvoid Table_Test()
{
	using namespace gnova;

	GTable<gint, gdouble, GString> table;
	table.AddRow(1, 1.1, GString("abc"));
	table.AddRow(2, 2.2, GString("def"));
	table.AddRow(3, 3.3, GString("xyz"));
					
	std::cout << "the table is: " << std::endl;
	std::cout << table.GetValue<0>(0)
		<< " " << table.GetValue<1>(0)
		<< " " << table.GetValue<2>(0).CString() << std::endl
		<< table.GetValue<0>(1)
		<< " " << table.GetValue<1>(1)
		<< " " << table.GetValue<2>(1).CString() << std::endl
		<< table.GetValue<0>(2)
		<< " " << table.GetValue<1>(2)
		<< " " << table.GetValue<2>(2).CString() << std::endl;

	table.SetValue<0>(0, 1111);
	table.SetValue<1>(0, 1111.1111);
	table.SetValue<2>(0, GString("birderyu"));

	std::cout << "now the table is: " << std::endl;
	std::cout << table.GetValue<0>(0)
		<< " " << table.GetValue<1>(0)
		<< " " << table.GetValue<2>(0).CString() << std::endl
		<< table.GetValue<0>(1)
		<< " " << table.GetValue<1>(1)
		<< " " << table.GetValue<2>(1).CString() << std::endl
		<< table.GetValue<0>(2)
		<< " " << table.GetValue<1>(2)
		<< " " << table.GetValue<2>(2).CString() << std::endl;
}
