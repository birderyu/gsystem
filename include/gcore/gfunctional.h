#ifndef _CORE_FUNCTIONAL_H_
#define _CORE_FUNCTIONAL_H_

#include <functional>
#include "gtype.h"

namespace gsystem { // gsystem

template<typename FunT>
class GFunction
	: public std::function<FunT>
{
public:
	GFunction() GNOEXCEPT
		: std::function<FunT>() {}

	GFunction(gnullptr n) GNOEXCEPT
		: std::function<FunT>(n) {}

	GFunction(const GFunction &func) GNOEXCEPT
		: std::function<FunT>(func) {}

	template<typename T>
	GFunction(T func) GNOEXCEPT
		: std::function<FunT>(func) {}
};

} // namespace gsystem

#endif // _CORE_FUNCTIONAL_H_