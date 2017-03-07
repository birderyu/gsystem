#ifndef _CORE_ENDIAN_H_
#define _CORE_ENDIAN_H_

#include "gglobal.h"

class GAPI GEndian
{
public:
	/// 将数字转换为大端字节数组
	/// 
	/// @param[in]	nValue 待转换的数字
	/// @parma[out]	nData 数字大端在前的字节序列
	/// @return void。
	static gvoid ToBigEndianBytes(guint16 nValue, gbyte nData[]);
	static gvoid ToBigEndianBytes(guint32 nValue, gbyte nData[]);
	static gvoid ToBigEndianBytes(guint64 nValue, gbyte nData[]);

	/// 将大端字节数组转换为数字
	/// 
	/// @param[in]	nData 大端在前的字节序列
	/// @param[out]	nValue 转换后的数字
	/// @return void。
	static gvoid ToBigEndianNumber(gbyte nData[], guint16 &nValue);
	static gvoid ToBigEndianNumber(gbyte nData[], guint32 &nValue);
	static gvoid ToBigEndianNumber(gbyte nData[], guint64 &nValue);

	/// 将数字转换为小端字节数组
	/// 
	/// @param[in]	nValue 待转换的数字
	/// @param[out]	nData 数字小端在前的字节序列
	/// @return void。
	static gvoid ToLittleEndianBytes(guint16 nValue, gbyte nData[]);
	static gvoid ToLittleEndianBytes(guint32 nValue, gbyte nData[]);
	static gvoid ToLittleEndianBytes(guint64 nValue, gbyte nData[]);
	
	/// 将小端字节数组转换为数字
	/// 
	/// @param[in]	nData 小端在前的字节序列
	/// @param[out]	nValue 转换后的数字
	/// @return void。
	static gvoid ToLittleEndianNumber(gbyte nData[], guint16 &nValue);
	static gvoid ToLittleEndianNumber(gbyte nData[], guint32 &nValue);
	static gvoid ToLittleEndianNumber(gbyte nData[], guint64 &nValue);

	static gbool Swap(gbool);
	static gchar Swap(gchar);
	static gschar Swap(gschar);
	static guchar Swap(guchar);
	static gshort Swap(gshort);
	static gushort Swap(gushort);
	static gint Swap(gint);
	static guint Swap(guint);
	static glong Swap(glong);
	static gulong Swap(gulong);
	static glonglong Swap(glonglong);
	static gulonglong Swap(gulonglong);
	static gfloat Swap(gfloat);
	static gdouble Swap(gdouble);
	static gdecimal Swap(gdecimal);

private:
	GEndian();
	GEndian(const GEndian&);
	~GEndian();
};

#include "gendian.inl"

#endif // _CORE_ENDIAN_H_
