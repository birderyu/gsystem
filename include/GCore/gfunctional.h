#pragma once
#include <functional>

namespace gnova {

/// std::function
template<class FunT>
class GFunction
	: public std::function<FunT>
{

};

}