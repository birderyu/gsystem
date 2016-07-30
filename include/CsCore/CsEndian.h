#ifndef _CSCORE_CSENDIAN_H_
#define _CSCORE_CSENDIAN_H_

#include "CsCoreGlobal.h"

class CsCore_Export CsEndian
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

protected:
	CsEndian();
	~CsEndian();
};

#endif // _CSCORE_CSENDIAN_H_
