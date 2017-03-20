#include "gencoding.h"

#define G_MAX_ENCODING_SIZE_OF_GBK	20902

#define G_START_UNICODE_OF_GBK		0x4E00
#define G_END_UNICODE_OF_GBK		0x9FA5
#define G_ILLEGAL_UNICODE			0x110000

namespace gsystem { // gsystem

GEncoding &GEncoding::Instance()
{
	if (GNULL == m_pEncoding)
	{
		m_pEncoding = new GEncoding();
	}
	return *m_pEncoding;
}

GEncoding *GEncoding::m_pEncoding = GNULL;

GEncoding::GEncoding()
{
	Initialize();
}

GEncoding::~GEncoding()
{
	Release();
}

gsize GEncoding::GbkStringToUtf8String(gcstring8 gbk, gsize size, gstring8 utf8)
{
	return 0;
}

gsize GEncoding::Utf8StringToGbkString(gcstring8 utf8, gsize size, gstring8 gbk)
{
	if (GNULL == unicode_gbk_basic || GNULL == utf8 || GNULL == gbk)
	{
		return 0;
	}
	gsize gbk_size = 0;
	gsize index = 0;
	while (index < size)
	{
		guint8 size_utf8c = GetUnitSizeOfUtf8Character(utf8 + index);
		if (size_utf8c == 0)
		{
			// 这是一个非法字符的utf8字符
			gbk[gbk_size++] = utf8[index++];
			continue;
		}

		guint32 unicode = Utf8CharacterToUnicode(utf8 + index);
		if (unicode < G_START_UNICODE_OF_GBK || unicode > G_END_UNICODE_OF_GBK)
		{
			// 当前的Unicode编码并非一个汉字，将它直接赋值给gbk字符
			for (gsize i = 0; i < size_utf8c; i++)
			{
				gbk[gbk_size++] = utf8[index++];
			}
		}
		else
		{
			// 当前的Unicode编码是一个汉字，将它转换为gbk编码后，赋值给gbk字符
			guint32 gbk_code = unicode_gbk_basic[unicode - G_START_UNICODE_OF_GBK];
			gbk[gbk_size++] = static_cast<gchar8>(0xFF & (gbk_code >> 8)); // 00000000 00000000 00000000 11111111
			gbk[gbk_size++] = static_cast<gchar8>(0xFF & gbk_code); // 00000000 00000000 00000000 11111111
			index += size_utf8c;
		}
	}

	gbk[gbk_size] = '\0';
	return gbk_size;
}

guint8 GEncoding::GetUnitSizeOfUtf8Character(const gchar8 *utf8)
{
	if (GNULL == utf8)
	{
		return 0;
	}
	if ((0x80 & utf8[0]) == 0) // 1000 0000
	{
		// 第1位为0
		return 1;
	}
	else
	{
		// 第1位不为0
		if ((0x20 & utf8[0]) == 0) // 0010 0000
		{
			// 第3位为0
			return 2;
		}
		else if ((0x10 & utf8[0]) == 0) // 0001 0000
		{
			// 第4位为0
			return 3;
		}
		else if ((0x8 & utf8[0]) == 0) // 0000 1000
		{
			// 第5位为0
			return 4;
		}
	}
	// 其他情况全部视为非法字符
	return 0;
}

guint32 GEncoding::Utf8CharacterToUnicode(const gchar8 *utf8)
{
	guint8 size = GetUnitSizeOfUtf8Character(utf8);
	if (size == 1)
	{
		return static_cast<guint32>(utf8[0]);
	}
	else if (size == 2)
	{
		return ((utf8[0] & 0x1F) << 6) // 0011 1111
			+ (utf8[1] & 0x3F); 
	}
	else if (size == 3)
	{
		return ((utf8[0] & 0xF) << 12)	// 0000 1111
			+ ((utf8[1] & 0x3F) << 6)	// 0011 1111
			+ (utf8[2] & 0x3F); 
	}
	else if (size == 4)
	{
		// 0000 1111, 0011 1111
		return ((utf8[0] & 0x7) << 18)	// 0000 0111
			+ ((utf8[1] & 0x3F) << 16)	// 0011 1111
			+ ((utf8[2] & 0x3F) << 6)	// 0011 1111
			+ (utf8[3] & 0x3F);
	}
	return G_ILLEGAL_UNICODE;
}

guint8 GEncoding::UnicodeToUtf8Character(guint32 unicode, gchar8 *utf8)
{
	if (GNULL == utf8)
	{
		return 0;
	}
	gsize size = 0;
	if (unicode <= 0x7F)
	{
		size = 1;
		utf8[0] = static_cast<gchar8>(0x7F & unicode); // 01111111 & u
	}
	else if (unicode <= 0x7FF)
	{
		size = 2;
		utf8[0] = static_cast<gchar8>(0xDF & (0x1F | (unicode >> 6))); // 11011111 & (00011111 | (u >> 6))
		utf8[1] = static_cast<gchar8>(0xBF & (0x3F | unicode)); // 10111111 & (00111111 | u)
	}
	else if (unicode <= 0xFFFF)
	{
		size = 3;
		utf8[0] = static_cast<gchar8>(0xEF & (0xF | (unicode >> 12))); // 11101111 & (00001111 | (u >> 12))
		utf8[1] = static_cast<gchar8>(0xBF & (0x3F | (unicode >> 6))); // 10111111 & (00111111 | (u >> 6))
		utf8[2] = static_cast<gchar8>(0xBF & (0x3F | unicode)); // 10111111 & (00111111 | u)
	}
	else if (unicode <= 0x10FFFF)
	{
		size = 4;
		utf8[0] = static_cast<gchar8>(0xF7 & (0x7 | (unicode >> 18))); // 11110111 & (00000111 | (u >> 18))
		utf8[1] = static_cast<gchar8>(0xBF & (0x3F | (unicode >> 12))); // 10111111 & (00111111 | (u >> 12))
		utf8[2] = static_cast<gchar8>(0xBF & (0x3F | (unicode >> 6))); // 10111111 & (00111111 | (u >> 6))
		utf8[3] = static_cast<gchar8>(0xBF & (0x3F | unicode)); // 10111111 & (00111111 | u)
	}
	return size;
}

guint8 GEncoding::UnicodeToUtf16Character(guint32 unicode, gchar16 *utf16)
{
	if (GNULL == utf16)
	{
		return 0;
	}
	gsize size = 0;
	if (unicode <= 0xFFFF)
	{
		size = 1;
	}
	else if (unicode <= 0x10FFFF)
	{
		size = 2;
	}
	return size;
}

gvoid GEncoding::Initialize()
{

}

gvoid GEncoding::Release()
{
	delete[] unicode_gbk_basic;
}

gbool GEncoding::HasGBK(guint32 unicode) const
{
	if (unicode >= G_START_UNICODE_OF_GBK && unicode <= G_END_UNICODE_OF_GBK)
	{
		return true;
	}
	else if (unicode <= 0x7F || unicode >= 0xFFFF)
	{
		return false;
	}
	return unicode_gbk_symbol.Contains(unicode);
}

} // namespace gsystem

#undef G_ILLEGAL_UNICODE
#undef G_END_UNICODE_OF_GBK
#undef G_START_UNICODE_OF_GBK
#undef G_MAX_ENCODING_SIZE_OF_GBK