#pragma once
#include <functional>

namespace gnova { // gnova

/// std::function
template<class FunT>
class GFunction
	: public std::function<FunT>
{

};

} // namespace gnova