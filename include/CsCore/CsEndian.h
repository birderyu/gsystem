#ifndef _CORE_ENDIAN_UTILITY_H_
#define _CORE_ENDIAN_UTILITY_H_

#include "CsGlobal.h"

class CS_API CsEndian
{
public:
	/// 将数字转换为大端字节数组
	/// 
	/// @param[in]	nValue 待转换的数字
	/// @parma[out]	nData 数字大端在前的字节序列
	/// @return void。
	static void ToBigEndianBytes(cs_uint16 nValue, cs_byte nData[]);
	static void ToBigEndianBytes(cs_uint32 nValue, cs_byte nData[]);
	static void ToBigEndianBytes(cs_uint64 nValue, cs_byte nData[]);

	/// 将大端字节数组转换为数字
	/// 
	/// @param[in]	nData 大端在前的字节序列
	/// @param[out]	nValue 转换后的数字
	/// @return void。
	static void ToBigEndianNumber(cs_byte nData[], cs_uint16 &nValue);
	static void ToBigEndianNumber(cs_byte nData[], cs_uint32 &nValue);
	static void ToBigEndianNumber(cs_byte nData[], cs_uint64 &nValue);

	/// 将数字转换为小端字节数组
	/// 
	/// @param[in]	nValue 待转换的数字
	/// @param[out]	nData 数字小端在前的字节序列
	/// @return void。
	static void ToLittleEndianBytes(cs_uint16 nValue, cs_byte nData[]);
	static void ToLittleEndianBytes(cs_uint32 nValue, cs_byte nData[]);
	static void ToLittleEndianBytes(cs_uint64 nValue, cs_byte nData[]);
	
	/// 将小端字节数组转换为数字
	/// 
	/// @param[in]	nData 小端在前的字节序列
	/// @param[out]	nValue 转换后的数字
	/// @return void。
	static void ToLittleEndianNumber(cs_byte nData[], cs_uint16 &nValue);
	static void ToLittleEndianNumber(cs_byte nData[], cs_uint32 &nValue);
	static void ToLittleEndianNumber(cs_byte nData[], cs_uint64 &nValue);

	static cs_bool Swap(cs_bool);
	static cs_char Swap(cs_char);
	static cs_schar Swap(cs_schar);
	static cs_uchar Swap(cs_uchar);
	static cs_short Swap(cs_short);
	static cs_ushort Swap(cs_ushort);
	static cs_int Swap(cs_int);
	static cs_uint Swap(cs_uint);
	static cs_long Swap(cs_long);
	static cs_ulong Swap(cs_ulong);
	static cs_longlong Swap(cs_longlong);
	static cs_ulonglong Swap(cs_ulonglong);
	static cs_float Swap(cs_float);
	static cs_double Swap(cs_double);
	static cs_decimal Swap(cs_decimal);

private:
	CsEndian();
	CsEndian(const CsEndian&);
	~CsEndian();
};

#endif // _CORE_ENDIAN_UTILITY_H_
