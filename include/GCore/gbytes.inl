#ifndef _CORE_BYTES_INLINE_
#define _CORE_BYTES_INLINE_

template<typename T> 
GINLINE gsize GBytes::ArithmeticToBytes(const T *val, gbyte *bytes)
{
	static_assert(GIsArithmetic<T>::value,
		"type must by arithmetic.");
	GASSERT(bytes && val);

	gsize size = sizeof(T);

#ifdef G_LITTLE_ENDIAN
	// 转换成大端字节序
	const gbyte *start = (const gbyte *)val;
	for (gsize i = 0; i < size; i++)
	{
		bytes[size - i] = start[i];
	}
#else // G_BIG_ENDIAN
	GMemCopy(bytes, val, size);
#endif // G_LITTLE_ENDIAN

	return size;
}

template<typename T> 
GINLINE gsize GBytes::BytesToArithmetic(const gbyte *bytes, T *val)
{
	static_assert(GIsArithmetic<T>::value,
		"type must by arithmetic.");
	GASSERT(bytes && val);

	gsize size = sizeof(T);

#ifdef G_LITTLE_ENDIAN
	// 转换成小端字节序
	gbyte *start = (gbyte *)val;
	for (gsize i = 0; i < size; i++)
	{
		start[i] = bytes[size - i];
	}
#else // G_BIG_ENDIAN
	GMemCopy(val, bytes, size);
#endif // G_LITTLE_ENDIAN

	return size;
}

#endif // _CORE_BYTES_INLINE_