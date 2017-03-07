#pragma once
#include <functional>

/// std::function
template<class FunT>
class GFunction
	: public std::function<FunT>
{

};