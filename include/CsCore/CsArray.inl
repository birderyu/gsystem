#ifndef _CORE_ARRAY_INLINE_
#define _CORE_ARRAY_INLINE_

template <typename DataT>
cs_uint CsArray<DataT>::ClassCode() const
{
	return CsArray<DataT>::CLASS_CODE;
}

#endif // _CORE_ARRAY_INLINE_