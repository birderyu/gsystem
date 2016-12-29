#ifndef _CORE_UNORDER_MAP_H_
#define _CORE_UNORDER_MAP_H_

#include "CsHashTable.h"

template <typename KeyT, typename ValueT,
	typename HashT = CsHashF<KeyT>,
	typename CompareT = CsEqualToF < KeyT >>
class CsUnorderMap
	: public CsObject
{
	/*
public:
	struct CsUnorderMapNode
		: public CsNextNodeT<CsUnorderMapNode>
		, public CsKeyValueNodeT<KeyT, ValueT>
		, public CsNewT<CsUnorderMapNode>
	{
		CsUnorderMapNode(const KeyT &key = KeyT(),
			const ValueT &value = ValueT(),
			CsUnorderMapNode *next = NULL)
			: CsNextNodeT<CsUnorderMapNode>(next)
			, CsKeyValueNodeT<KeyT, ValueT>(key, value)
		{

		}
	};
	typedef CsUnorderMapNode Node;

public:
	CsUnorderMap();

private:
	CsHashTable<KeyT, ValueT, HashT, CompareT, CsUnorderMapNode> m_tTable;
	cs_size_t m_nSize;
	*/
};

#endif // _CORE_UNORDER_MAP_H_