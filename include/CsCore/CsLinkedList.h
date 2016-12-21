#ifndef _CORE_LINKED_LIST_H_
#define _CORE_LINKED_LIST_H_

#include "CsObject.h"
#include "CsSerialize.h"
#include "CsStructure.h"

template<typename DataT>
class CsLinkedList
	: public CsListT<CsLinkedList<DataT>>
	, public CsObject
{
public:
	enum { CLASS_CODE = CLASS_CODE_LINKED_LIST, };

public:
	virtual ~CsLinkedList() = 0 {}
	virtual cs_void Invert() = 0;
	virtual cs_bool IsEmpty() const = 0;
	virtual cs_size_t Size() const = 0;
	virtual cs_bool InsertBefore(cs_size_t pos, const DataT &data) = 0;
	virtual cs_bool InsertAfter(cs_size_t pos, const DataT &data) = 0;
	virtual cs_bool AddHead(const DataT &data) = 0;
	virtual cs_bool AddTail(const DataT &data) = 0;
	virtual cs_void RemoveAt(cs_size_t pos) = 0;
	virtual cs_void RemoveHead() = 0;
	virtual cs_void RemoveTail() = 0;
	virtual cs_void RemoveAll() = 0;
	virtual DataT& GetTail() = 0;
	virtual DataT  GetTail() const = 0;
	virtual DataT& GetHead() = 0;
	virtual DataT  GetHead() const = 0;
	virtual DataT& GetAt(cs_size_t pos) = 0;
	virtual DataT  GetAt(cs_size_t pos) const = 0;
	virtual cs_void SetAt(cs_size_t pos, const DataT &data) = 0;
	virtual cs_size_t Find(const DataT &data) const = 0;
	virtual cs_size_t FindCircle() const = 0;
	virtual DataT &operator[](cs_size_t id) = 0;
	virtual DataT operator[](cs_size_t id) const = 0;

	///
	virtual cs_uint ClassCode() const;
};

#include "CsLinkedList.inl"

#endif // _CORE_LINKED_LIST_H_