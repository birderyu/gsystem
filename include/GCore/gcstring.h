#ifndef _CORE_C_STRING_HELPER_H_
#define _CORE_C_STRING_HELPER_H_

#include "gglobal.h"

#define G_USE_MSVC_STRCMP

#ifdef G_COMPILER_MSVC
#	ifdef G_USE_MSVC_STRCMP
#	define strcasecmp	_stricmp
#	define strncasecmp	_strnicmp 
#	else // !G_USE_MSVC_STRCMP
GAPI gsystem::gint strcasecmp(const gsystem::gchar8 *s1, gsystem::gchar8 *s2);
GAPI gsystem::gint strncasecmp(const gsystem::gchar8 *s1, gsystem::gchar8 *s2, /*register*/ gsystem::gint n);
#	endif // G_USE_MSVC_STRCMP
#endif // G_COMPILER_MSVC

namespace gsystem { // gsystem

class GAPI GCChar
{
	gchar8 ToLower(gchar8);
	gchar16 ToLower(gchar16);
	gchar16 ToLower(gchar16);

	gchar8 ToUpper(gchar8);
	gchar16 ToUpper(gchar16);
	gchar16 ToUpper(gchar16);
};

// C风格的字符串操作
class GAPI GCString
{
public:
	// 不包含'\0'的长度
	static gsize Size(gcstring8 str);
	static gsize Size(gcstring16 str);
	static gsize Size(gcstring32 str);

	static gvoid Copy(gcstring8 src, gstring8 dest);
	static gvoid Copy(gcstring16 src, gstring16 dest);
	static gvoid Copy(gcstring32 src, gstring32 dest);

	// size = strlen(src) + 1（末尾的'\0'）
	static gvoid Copy(gcstring8 src, gsize size, gstring8 dest);
	static gvoid Copy(gcstring16 src, gsize size, gstring16 dest);
	static gvoid Copy(gcstring32 src, gsize size, gstring32 dest);

	static gvoid Trim(gcstring8 src, gsize size, gstring8 str_out, gsize &size_out);
	static gvoid Trim(gcstring16 src, gsize size, gstring16 str_out, gsize &size_out);
	static gvoid Trim(gcstring32 src, gsize size, gstring32 str_out, gsize &size_out);

	static gvoid TrimLeft(gcstring8 src, gsize size, gstring8 str_out, gsize &size_out);
	static gvoid TrimLeft(gcstring16 src, gsize size, gstring16 str_out, gsize &size_out);
	static gvoid TrimLeft(gcstring32 src, gsize size, gstring32 str_out, gsize &size_out);

	static gvoid TrimRight(gcstring8 src, gsize size, gstring8 str_out, gsize &size_out);
	static gvoid TrimRight(gcstring16 src, gsize size, gstring16 str_out, gsize &size_out);
	static gvoid TrimRight(gcstring32 src, gsize size, gstring32 str_out, gsize &size_out);

	static gvoid MakeTrim(gstring8 src, gsize size, gsize &size_out);
	static gvoid MakeTrim(gstring16 src, gsize size, gsize &size_out);
	static gvoid MakeTrim(gstring32 src, gsize size, gsize &size_out);

	static gvoid MakeTrimLeft(gstring8 src, gsize size, gsize &size_out);
	static gvoid MakeTrimLeft(gstring16 src, gsize size, gsize &size_out);
	static gvoid MakeTrimLeft(gstring32 src, gsize size, gsize &size_out);

	static gvoid MakeTrimRight(gstring8 src, gsize size, gsize &size_out);
	static gvoid MakeTrimRight(gstring16 src, gsize size, gsize &size_out);
	static gvoid MakeTrimRight(gstring32 src, gsize size, gsize &size_out);

	static gvoid MakeUpper(gstring8 src, gsize size);
	static gvoid MakeUpper(gstring16 src, gsize size);
	static gvoid MakeUpper(gstring32 src, gsize size);

	static gvoid MakeLower(gstring8 src, gsize size);
	static gvoid MakeLower(gstring16 src, gsize size);
	static gvoid MakeLower(gstring32 src, gsize size);

	static gint Matcher(gcstring8 src, gsize size, gchar8 ptn, gbool isSensitive);
	static gint Matcher(gcstring16 src, gsize size, gchar16 ptn, gbool isSensitive);
	static gint Matcher(gcstring32 src, gsize size, gchar32 ptn, gbool isSensitive);

	static gint Matcher(gcstring8 src, gsize size, gcstring8 ptn, gsize psize, gbool isSensitive);
	static gint Matcher(gcstring16 src, gsize size, gcstring16 ptn, gsize psize, gbool isSensitive);
	static gint Matcher(gcstring32 src, gsize size, gcstring32 ptn, gsize psize, gbool isSensitive);

	// Boyer-Moore匹配算法
	//static gint BoyerMooreMatcher(gcstring src, gsize slen, gcstring ptn, gsize plen, gbool isSensitive);

	// 注意：当返回值为false时，表示未做任何替换，此时c_str_out和out_len里的值可能是无效的
	static gbool Replace(gcstring8 src, gsize size,
		gcstring8 from, gsize from_size,
		gcstring8 to, gsize to_size,
		gbool isSensitive,
		gstring8 str_out, gsize &out_size);
	static gbool Replace(gcstring16 src, gsize size,
		gcstring16 from, gsize from_size,
		gcstring16 to, gsize to_size,
		gbool isSensitive,
		gstring16 str_out, gsize &out_size);
	static gbool Replace(gcstring32 src, gsize size,
		gcstring32 from, gsize from_size,
		gcstring32 to, gsize to_size,
		gbool isSensitive,
		gstring32 str_out, gsize &out_size);
};

} // namespace gsystem

#endif // _CORE_C_STRING_HELPER_H_