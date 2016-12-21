#ifndef _CORE_STRING_BUFFER_H_
#define _CORE_STRING_BUFFER_H_

#include "CsObject.h"
#include "CsStructure.h"
#include "CsBlock.h"
#include "CsString.h"

#define CS_STRING_BUFFER_DEFAULT_CAPACITY 2048
#define CS_STRING_BUFFER_DEFAULT_ADD_SIZE 512

class CS_API CsStringBuffer
	: public CsListT<CsStringBuffer>
	, public CsObject
{
public:
	CsStringBuffer(cs_size_t nCapacity = CS_STRING_BUFFER_DEFAULT_CAPACITY,
		cs_size_t nAddSize = CS_STRING_BUFFER_DEFAULT_ADD_SIZE);
	CsStringBuffer(const CsString &);
	CsStringBuffer(const CsStringBuffer &);
	~CsStringBuffer();

	cs_bool Reserve(cs_size_t);
	cs_void Clear();
	cs_void Dispose();

	CsStringBuffer &Append(cs_char);
	CsStringBuffer &Append(cs_cstring);
	CsStringBuffer &Append(const CsString &);

private:
	CsBlock<cs_char> m_tBlock;
};

#undef CS_STRING_BUFFER_DEFAULT_ADD_SIZE
#undef CS_STRING_BUFFER_DEFAULT_CAPACITY

#endif // _CORE_STRING_BUFFER_H_