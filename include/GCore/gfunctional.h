#pragma once
#include <functional>

namespace gsystem { // gsystem

/// std::function
template<class FunT>
class GFunction
	: public std::function<FunT>
{

};

} // namespace gsystem
