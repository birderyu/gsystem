#ifndef _CORE_ENCODING_H_
#define _CORE_ENCODING_H_

#include "gunordermap.h"

namespace gsystem { // gsystem

class GAPI GEncoding
{
public:
	static GEncoding &Instance();

	// 获取UTF-8编码实际的字符数（可能多个字符单元表示一个字符）
	static gsize GetLengthOfUtf8String(gcstring8 utf8);
	static gsize GetLengthOfUtf8String(gcstring8 utf8, gsize size);
	static gsize GetLengthOfGbkString(gcstring8 gbk);
	static gsize GetLengthOfGbkString(gcstring8 gbk, gsize size);

	/// 查看一个UTF-8字符占了多少字节
	/// utf8表示一个UTF-8字符的首地址
	/// 返回值可能为0、1、2、3、4，其中0代表非法，1、2、3、4代表占据的字节数量
	static guint8 GetUnitSizeOfUtf8Character(const gchar8 *utf8);

	static gsize GetUnitSizeOfUtf8CharacterFromUnicode();

	// 将一个UTF-8字符转为对应的Unicode编码
	static guint32 Utf8CharacterToUnicode(const gchar8 *utf8);

	// 将一个Unicode编码转换为对应的UTF-8字符，返回字符占据的元素单位的个数
	static guint8 UnicodeToUtf8Character(guint32 unicode, gchar8 *utf8);

	// 将一个Unicode编码转换为对应的UTF-16字符，返回字符占据的元素单位的个数
	static guint8 UnicodeToUtf16Character(guint32 unicode, gchar16 *utf16);

	// 将一个Unicode编码转换为对应的UTF-32字符，返回字符占据的元素单位的个数
	static guint8 UnicodeToUtf32Character(guint32 unicode, gchar32 *utf32);

public:
	// 将一个长度为size的GBK字符串转换为表示相同内容的UTF-8字符串，返回UTF-8字符串的长度
	gsize GbkStringToUtf8String(gcstring8 gbk, gsize size, gstring8 utf8);
	gsize GbkStringToUtf16String(gcstring8 gbk, gsize size, gstring16 utf16);
	gsize GbkStringToUtf32String(gcstring8 gbk, gsize size, gstring32 utf32);

	// 将一个长度为size的UTF-8字符串转换为表示相同内容的GBK字符串，返回GBK字符串的长度
	gsize Utf8StringToGbkString(gcstring8 utf8, gsize size, gstring8 gbk);
	gsize Utf8StringToUtf16String(gcstring8 utf8, gsize size, gstring16 utf16);
	gsize Utf8StringToUtf32String(gcstring8 utf8, gsize size, gstring32 utf32);

	gsize Utf16StringToGbkString(gcstring16 utf16, gsize size, gstring8 gbk);

private:
	GEncoding();
	~GEncoding();
	GEncoding(const GEncoding &) = delete;
	GEncoding &operator=(const GEncoding &) = delete;

	gvoid Initialize();
	gvoid Release();

	gbool HasGBK(guint32 unicode) const;

	// Unicode与GBK的对应表（基本汉字）
	guint16 *unicode_gbk_basic;

	// Unicode与GBK的对应表（符号）
	GUnorderMap<guint16, guint16> unicode_gbk_symbol;

	// GBK与Unicode的对应表
	GUnorderMap<guint16, guint16> gbk_unicode;

private:
	static GEncoding *m_pEncoding;
};

} // namespace gsystem

#endif // _CORE_ENCODING_H_