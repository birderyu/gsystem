#ifndef _CORE_LIST_H_
#define _CORE_LIST_H_

#include "CsDoubleLinkedList.h"

template <typename DataT>
class CsList 
	: public CsListT<CsList<DataT>>
	, public CsObject
{

};

#endif // _CORE_LIST_H_