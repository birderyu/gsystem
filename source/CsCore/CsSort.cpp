#include "CsSort.h"

cs_size_t CsSort_Private::LeftChild(const cs_size_t i)
{
	return 2 * i + 1;
}