#include "gcstring.h"
#include "gmemory.h"
#include <string.h>
#include <ctype.h>

#ifdef _MSC_VER
#	ifndef G_USE_MSVC_STRCMP
gsystem::gint strcasecmp(const gsystem::gchar *s1, gsystem::gchar *s2)
{
	while (::toupper((gsystem::guchar)*s1) == ::toupper((gsystem::guchar)*s2++))
		if (*s1++ == '\0') return 0;
	return(::toupper((gsystem::guchar)*s1) - ::toupper((gsystem::guchar)*--s2));
}

gsystem::gint strncasecmp(const gsystem::gchar *s1, gsystem::gchar *s2, /*register*/ gsystem::gint n)
{
	while (--n >= 0 && ::toupper((gsystem::guchar)*s1) == ::toupper((gsystem::guchar)*s2++))
		if (*s1++ == '\0')  return 0;
	return(n < 0 ? 0 : ::toupper((gsystem::guchar)*s1) - ::toupper((gsystem::guchar)*--s2));
}
#	endif // !G_USE_MSVC_STRCMP
#endif

namespace gsystem {
namespace detail {
namespace cstring {

template<typename StringT>
gsize Size(StringT str)
{
	if (GNULL == str)
	{
		return 0;
	}
	gsize i = 0;
	while (str[i++]) {}
	return i - 1;
}

}
}
}

namespace gsystem { // gsystem

gsize GCString::Size(gcstring8 str)
{
	if (GNULL == str)
	{
		return 0;
	}
	return ::strlen(str);
}

gsize GCString::Size(gcstring16 str)
{
	return detail::cstring::Size<gcstring16>(str);
}

gsize GCString::Size(gcstring32 str)
{
	return detail::cstring::Size<gcstring32>(str);
}

gvoid GCString::Copy(gcstring8 src, gsize size, gstring8 dest)
{
	GMemCopy(dest, src, size);
}

gvoid GCString::Trim(gcstring8 c_str, gsize size,
	gstring8 out_c_str, gsize &out_size)
{
	out_size = 0;
	if (size <= 0)
	{
		return;
	}
	gsize first_no_empty = 0;
	for (first_no_empty = 0; first_no_empty < size; first_no_empty++)
	{
		if (c_str[first_no_empty] != ' ')
		{
			break;
		}
	}
	if (first_no_empty >= size)
	{
		out_size = 0;
		out_c_str[0] = '\0';
		return;
	}

	// 这里不需要复制末尾的'\0'，因为函数的最后会单独赋值
	GCString::Copy(c_str + first_no_empty, size - first_no_empty, out_c_str);
	out_size = size - first_no_empty;

	gint last_no_empty = out_size - 1;
	for (last_no_empty = out_size - 1; last_no_empty >= 0; last_no_empty--)
	{
		if (out_c_str[last_no_empty] != ' ')
		{
			break;
		}
	}
	if (last_no_empty < 0)
	{
		out_size = 0;
		out_c_str[0] = '\0';
		return;
	}

	out_size = last_no_empty + 1;
	out_c_str[out_size] = '\0';
}

gvoid GCString::TrimLeft(gcstring8 c_str, gsize size,
	gstring8 out_c_str, gsize &out_size)
{
	out_size = 0;
	if (size <= 0)
	{
		return;
	}
	gsize first_no_empty = 0;
	for (first_no_empty = 0; first_no_empty < size; first_no_empty++)
	{
		if (c_str[first_no_empty] != ' ')
		{
			break;
		}
	}
	if (first_no_empty >= size)
	{
		out_size = 0;
		out_c_str[0] = '\0';
		return;
	}

	// 这里不需要复制末尾的'\0'，因为函数的最后会单独赋值
	GCString::Copy(c_str + first_no_empty, size - first_no_empty, out_c_str);
	out_size = size - first_no_empty;
	out_c_str[out_size] = '\0';
}

gvoid GCString::TrimRight(gcstring8 c_str, gsize size,
	gstring8 out_c_str, gsize &out_size)
{
	out_size = 0;
	if (size <= 0)
	{
		return;
	}
	// 这里不需要复制末尾的'\0'，因为函数的最后会单独赋值
	GCString::Copy(c_str, size, out_c_str);
	out_size = size;
	gint last_no_empty = out_size - 1;
	for (last_no_empty = out_size - 1; last_no_empty >= 0; last_no_empty--)
	{
		if (out_c_str[last_no_empty] != ' ')
		{
			break;
		}
	}
	if (last_no_empty < 0)
	{
		out_size = 0;
		out_c_str[0] = '\0';
		return;
	}

	out_size = last_no_empty + 1;
	out_c_str[out_size] = '\0';
}

gvoid GCString::MakeTrim(gstring8 c_str, gsize size, gsize &out_size)
{
	MakeTrimLeft(c_str, size, out_size);
	MakeTrimRight(c_str, out_size, out_size);
}

gvoid GCString::MakeTrimLeft(gstring8 c_str, gsize size, gsize &out_size)
{
	out_size = 0;
	if (size <= 0)
	{
		return;
	}
	gsize first_no_empty = 0;
	for (first_no_empty = 0; first_no_empty < size; first_no_empty++)
	{
		if (c_str[first_no_empty] != ' ')
		{
			break;
		}
	}

	if (first_no_empty >= size)
	{
		out_size = 0;
		c_str[0] = '\0';
		return;
	}

	else if (first_no_empty != 0)
	{
		GMemMove(c_str, c_str + first_no_empty, size - first_no_empty);
		out_size = size - first_no_empty;
		c_str[out_size] = '\0';
	}
}

gvoid GCString::MakeTrimRight(gstring8 c_str, gsize size, gsize &out_size)
{
	out_size = size;
	if (size <= 0)
	{
		return;
	}
	gsize last_no_empty = out_size - 1;
	for (last_no_empty = out_size - 1; last_no_empty >= 0; last_no_empty--)
	{
		if (c_str[last_no_empty] != ' ')
		{
			break;
		}
	}

	if (last_no_empty < 0)
	{
		out_size = 0;
		c_str[0] = '\0';
		return;
	}

	out_size = last_no_empty + 1;
	c_str[out_size] = '\0';
}

gvoid GCString::MakeUpper(gstring8 c_str, gsize size)
{
	for (gsize i = 0; i < size; i++)
	{
		if (c_str[i] >= 'a'&&c_str[i] <= 'z')
		{
			c_str[i] -= ('a' - 'A');
		}
	}
}

gvoid GCString::MakeLower(gstring8 c_str, gsize size)
{
	for (gsize i = 0; i < size; i++)
	{
		if (c_str[i] >= 'A'&&c_str[i] <= 'Z')
		{
			c_str[i] += ('a' - 'A');
		}
	}
}

gint GCString::Matcher(gcstring8 src, gsize size, gchar ptn, gbool isSensitive)
{
	if (isSensitive)
	{
		ptn = G_CHAR_TO_LOWER(ptn);
	}
	for (gsize i = 0; i < size; ++i)
	{
		if (!isSensitive)
		{
			gchar _c = src[i];
			_c = G_CHAR_TO_LOWER(_c);
			if (_c == ptn)
			{
				return i;
			}
		}
		else
		{
			if (src[i] == ptn)
			{
				return i;
			}
		}
	}
	return -1;
}

gint GCString::Matcher(gcstring8 src, gsize slen, gcstring8 ptn, gsize plen, gbool isSensitive)
{
	if (plen == 0)
	{
		return -1;
	}
	if (plen == 1)
	{
		return GCString::Matcher(src, slen, ptn[0], isSensitive);
	}

	gsize i = 0, j = 0;
	while (j < plen && i < slen) 
	{
		if (isSensitive)
		{
			// 大小写敏感
			if (src[i] == ptn[j])
			{
				i++;
				j++;
			}
			else
			{
				i = i - j + 1;
				j = 0;
			}
		}
		else
		{
			// 大小写不敏感
			gchar c1 = G_CHAR_TO_UPPER(src[i]);
			gchar c2 = G_CHAR_TO_UPPER(ptn[j]);
			if (c1 == c2)
			{
				i++;
				j++;
			}
			else
			{
				i = i - j + 1;
				j = 0;
			}
		}
	}
	if (j == plen)
		return i - plen;
	else
		return -1;
}

gbool GCString::Replace(gcstring8 c_str, gsize len,
	gcstring8 from, gsize from_len,
	gcstring8 to, gsize to_len,
	gbool isSensitive,
	gstring8 c_str_out, gsize &out_len)
{
	if (len <= 0 || from_len <= 0)
	{
		return false;
	}

	gsize start = 0;
	out_len = 0;
	for (gsize i = 0; i <= len - from_len;)
	{
		gint ret = 0;
		if (isSensitive)
		{
			ret = ::strncmp(c_str + i, from, from_len);
		}
		else
		{
			ret = ::strncasecmp(c_str + i, from, from_len);
		}
		if (ret != 0)
		{
			i++;
			continue;
		}
		if (i > start)
		{
			gsize _len_ = i - start;
			GCString::Copy(c_str + start, _len_, c_str_out + out_len);
			out_len += _len_;
		}
		GCString::Copy(to, to_len, c_str_out + out_len);
		out_len += to_len;
		i += from_len;
		start = i;
	}
	if (start <= 0)
	{
		return false;
	}
	gsize _len_ = len - start;
	GCString::Copy(c_str + start, _len_, c_str_out + out_len);
	out_len += _len_;
	c_str_out[out_len] = '\0';
	return true;
}

} // namespace gsystem
