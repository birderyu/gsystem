#include <gtest/gtest.h>
#include "typedef_test.h"
#include "series_test.h"
#include "binaryheap_test.h"
#include "stack_test.h"
#include "queue_test.h"
#include "gfunctional.h"

#include <string>
#include "gserialize.h"
#include "gserializable.h"

using namespace gsystem;

class A : public GSerializable
{
public:
	gvoid AA() const {};
};

class B : public A
{

};

class C : public GObject
{

};


gint main(gint argc, gchar *argv[])
{
	gbool b_a_s = GIsBaseOf<GSerializable, A>::value;
	gbool b_b_s = GIsBaseOf<GSerializable, B>::value;
	gbool b_c_s = GIsBaseOf<GSerializable, GObject>::value;

	gbool b_a = detail::GHasSerializeFunction<B>::value;
	gbool b_o = detail::GHasSerializeFunction<GObject>::value;

	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
}