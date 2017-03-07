#pragma once

#include "gstatictable.h"
#include <vector>
gvoid StaticTable_Test()
{
	std::initializer_list<int> a;
	GStaticTable<3, gint, gdouble, GString> table;
	table.SetRow<0>(1, 1.1, GString("abc"));
	table.SetRow<1>(2, 2.2, GString("def"));
	table.SetRow<2>(3, 3.3, GString("xyz"));
					
	std::cout << "the table is: " << std::endl;
	std::cout << table.GetValue<0, 0>()
		<< " " << table.GetValue<0, 1>()
		<< " " << table.GetValue<0, 2>().CString() << std::endl
		<< table.GetValue<1, 0>()
		<< " " << table.GetValue<1, 1>()
		<< " " << table.GetValue<1, 2>().CString() << std::endl
		<< table.GetValue<2, 0>()
		<< " " << table.GetValue<2, 1>()
		<< " " << table.GetValue<2, 2>().CString() << std::endl;

	table.SetValue<0, 0>(1111);
	table.SetValue<0, 1>(1111.1111);
	table.SetValue<0, 2>(GString("birderyu"));

	std::cout << "now the table is: " << std::endl;
	std::cout << table.GetValue<0, 0>()
		<< " " << table.GetValue<0, 1>()
		<< " " << table.GetValue<0, 2>().CString() << std::endl
		<< table.GetValue<1, 0>()
		<< " " << table.GetValue<1, 1>()
		<< " " << table.GetValue<1, 2>().CString() << std::endl
		<< table.GetValue<2, 0>()
		<< " " << table.GetValue<2, 1>()
		<< " " << table.GetValue<2, 2>().CString() << std::endl;

	//gint v_0_0 = table.GetValue<0, 0>();
	//gdouble v_0_1 = table.GetValue<0, 1>();
	//GString v_0_2 = table.GetValue<0, 2>();
	//gint v_1_0 = table.GetValue<1, 0>();
	//gdouble v_1_1 = table.GetValue<1, 1>();
	//GString v_1_2 = table.GetValue<1, 2>();
	//gint v_2_0 = table.GetValue<2, 0>();
	//gdouble v_2_1 = table.GetValue<2, 1>();
	//GString v_2_2 = table.GetValue<2, 2>();

	gint stop = 1;
	stop++;
}
