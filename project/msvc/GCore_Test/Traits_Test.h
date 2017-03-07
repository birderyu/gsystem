#include "gtraits.h"

class AClassWithNothing
{
	
};

class AClassWithoutDefaultConstructible
{
public:
	AClassWithoutDefaultConstructible(const AClassWithoutDefaultConstructible &) {}
	AClassWithoutDefaultConstructible(AClassWithoutDefaultConstructible &&) {}
};

gvoid TestTraits()
{
	using TestClass = AClassWithoutDefaultConstructible;

	gbool v1 = GIsDefaultConstructible<TestClass>::value;
	gbool _v1 = std::is_default_constructible<TestClass>::value;
	gbool v2 = GIsCopyConstructible<TestClass>::value;
	gbool _v2 = std::is_copy_constructible<TestClass>::value;
	gbool v3 = GIsMoveConstructible<TestClass>::value;
	gbool _v3 = std::is_move_constructible<TestClass>::value;

	gint stop = 1;
	stop++;
}
