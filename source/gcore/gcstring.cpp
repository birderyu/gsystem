#include "gcstring.h"
#include "gmemory.h"
#include <string.h>
#include <ctype.h>

#ifdef _MSC_VER
#	ifndef G_USE_MSVC_STRCMP
gsystem::gint strcasecmp(const gsystem::gchar8 *s1, gsystem::gchar8 *s2)
{
	while (::toupper((gsystem::guchar)*s1) == ::toupper((gsystem::guchar)*s2++))
		if (*s1++ == '\0') return 0;
	return(::toupper((gsystem::guchar)*s1) - ::toupper((gsystem::guchar)*--s2));
}

gsystem::gint strncasecmp(const gsystem::gchar8 *s1, gsystem::gchar8 *s2, /*register*/ gsystem::gint n)
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

static const gchar8 digits_8[] = "9876543210123456789";
static const gchar8* zero_8 = digits_8 + 9;
static_assert(sizeof(digits_8) == 20, "");

template<typename T>
gvoid GReverse(T* begin, T* end)
{
	for (; begin != end && begin != --end; ++begin)
	{
		GSwap(*begin, *end);
	}
}

template<typename T>
gsize GConvert(T value, gstring8 buf)
{
	T i = value;
	gchar8* p = buf;

	do
	{
		gint lsd = i % 10;
		i /= 10;
		*p++ = zero_8[lsd];
	} while (i != 0);

	if (value < 0)
	{
		*p++ = '-';
	}
	*p = '\0';
	GReverse(buf, p);
	return p - buf;
}

}
}
}

namespace gsystem { // gsystem

gcstring8 GCString::Number(gint value, gstring8 buf)
{
	return GNULL;
}

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
	if (GNULL == str)
	{
		return 0;
	}
	gsize i = 0;
	while (str[i++]) {}
	return i - 1;
}

gsize GCString::Size(gcstring32 str)
{
	if (GNULL == str)
	{
		return 0;
	}
	gsize i = 0;
	while (str[i++]) {}
	return i - 1;
}

gvoid GCString::Copy(gcstring8 src, gstring8 dest)
{
	Copy(src, Size(src) + 1, dest);
}

gvoid GCString::Copy(gcstring16 src, gstring16 dest)
{
	Copy(src, Size(src) + 1, dest);
}

gvoid GCString::Copy(gcstring32 src, gstring32 dest)
{
	Copy(src, Size(src) + 1, dest);
}

gvoid GCString::Copy(gcstring8 src, gsize size, gstring8 dest)
{
	GMemCopy(dest, src, size);
}

gvoid GCString::Copy(gcstring16 src, gsize size, gstring16 dest)
{
	GMemCopy(dest, src, size * 2);
}

gvoid GCString::Copy(gcstring32 src, gsize size, gstring32 dest)
{
	GMemCopy(dest, src, size * 4);
}

gvoid GCString::Trim(gcstring8 src, gsize size, gstring8 str_out, gsize &size_out)
{
	size_out = 0;
	if (size <= 0)
	{
		return;
	}
	gsize first_no_empty = 0;
	for (first_no_empty = 0; first_no_empty < size; first_no_empty++)
	{
		if (src[first_no_empty] != ' ')
		{
			break;
		}
	}
	if (first_no_empty >= size)
	{
		size_out = 0;
		str_out[0] = '\0';
		return;
	}

	// 这里不需要复制末尾的'\0'，因为函数的最后会单独赋值
	GCString::Copy(src + first_no_empty, size - first_no_empty, str_out);
	size_out = size - first_no_empty;

	gint last_no_empty = size_out - 1;
	for (last_no_empty = size_out - 1; last_no_empty >= 0; last_no_empty--)
	{
		if (str_out[last_no_empty] != ' ')
		{
			break;
		}
	}
	if (last_no_empty < 0)
	{
		size_out = 0;
		str_out[0] = '\0';
		return;
	}

	size_out = last_no_empty + 1;
	str_out[size_out] = '\0';
}

gvoid GCString::Trim(gcstring16 src, gsize size, gstring16 str_out, gsize &size_out)
{
	size_out = 0;
	if (size <= 0)
	{
		return;
	}
	gsize first_no_empty = 0;
	for (first_no_empty = 0; first_no_empty < size; first_no_empty++)
	{
		if (src[first_no_empty] != ' ')
		{
			break;
		}
	}
	if (first_no_empty >= size)
	{
		size_out = 0;
		str_out[0] = '\0';
		return;
	}

	// 这里不需要复制末尾的'\0'，因为函数的最后会单独赋值
	GCString::Copy(src + first_no_empty, size - first_no_empty, str_out);
	size_out = size - first_no_empty;

	gint last_no_empty = size_out - 1;
	for (last_no_empty = size_out - 1; last_no_empty >= 0; last_no_empty--)
	{
		if (str_out[last_no_empty] != ' ')
		{
			break;
		}
	}
	if (last_no_empty < 0)
	{
		size_out = 0;
		str_out[0] = '\0';
		return;
	}

	size_out = last_no_empty + 1;
	str_out[size_out] = '\0';
}

gvoid GCString::Trim(gcstring32 src, gsize size, gstring32 str_out, gsize &size_out)
{
	size_out = 0;
	if (size <= 0)
	{
		return;
	}
	gsize first_no_empty = 0;
	for (first_no_empty = 0; first_no_empty < size; first_no_empty++)
	{
		if (src[first_no_empty] != ' ')
		{
			break;
		}
	}
	if (first_no_empty >= size)
	{
		size_out = 0;
		str_out[0] = '\0';
		return;
	}

	// 这里不需要复制末尾的'\0'，因为函数的最后会单独赋值
	GCString::Copy(src + first_no_empty, size - first_no_empty, str_out);
	size_out = size - first_no_empty;

	gint last_no_empty = size_out - 1;
	for (last_no_empty = size_out - 1; last_no_empty >= 0; last_no_empty--)
	{
		if (str_out[last_no_empty] != ' ')
		{
			break;
		}
	}
	if (last_no_empty < 0)
	{
		size_out = 0;
		str_out[0] = '\0';
		return;
	}

	size_out = last_no_empty + 1;
	str_out[size_out] = '\0';
}

gvoid GCString::TrimLeft(gcstring8 src, gsize size, gstring8 str_out, gsize &size_out)
{
	size_out = 0;
	if (size <= 0)
	{
		return;
	}
	gsize first_no_empty = 0;
	for (first_no_empty = 0; first_no_empty < size; first_no_empty++)
	{
		if (src[first_no_empty] != ' ')
		{
			break;
		}
	}
	if (first_no_empty >= size)
	{
		size_out = 0;
		str_out[0] = '\0';
		return;
	}

	// 这里不需要复制末尾的'\0'，因为函数的最后会单独赋值
	GCString::Copy(src + first_no_empty, size - first_no_empty, str_out);
	size_out = size - first_no_empty;
	str_out[size_out] = '\0';
}

gvoid GCString::TrimLeft(gcstring16 src, gsize size, gstring16 str_out, gsize &size_out)
{
	size_out = 0;
	if (size <= 0)
	{
		return;
	}
	gsize first_no_empty = 0;
	for (first_no_empty = 0; first_no_empty < size; first_no_empty++)
	{
		if (src[first_no_empty] != ' ')
		{
			break;
		}
	}
	if (first_no_empty >= size)
	{
		size_out = 0;
		str_out[0] = '\0';
		return;
	}

	// 这里不需要复制末尾的'\0'，因为函数的最后会单独赋值
	GCString::Copy(src + first_no_empty, size - first_no_empty, str_out);
	size_out = size - first_no_empty;
	str_out[size_out] = '\0';
}

gvoid GCString::TrimLeft(gcstring32 src, gsize size, gstring32 str_out, gsize &size_out)
{
	size_out = 0;
	if (size <= 0)
	{
		return;
	}
	gsize first_no_empty = 0;
	for (first_no_empty = 0; first_no_empty < size; first_no_empty++)
	{
		if (src[first_no_empty] != ' ')
		{
			break;
		}
	}
	if (first_no_empty >= size)
	{
		size_out = 0;
		str_out[0] = '\0';
		return;
	}

	// 这里不需要复制末尾的'\0'，因为函数的最后会单独赋值
	GCString::Copy(src + first_no_empty, size - first_no_empty, str_out);
	size_out = size - first_no_empty;
	str_out[size_out] = '\0';
}

gvoid GCString::TrimRight(gcstring8 src, gsize size, gstring8 str_out, gsize &size_out)
{
	size_out = 0;
	if (size <= 0)
	{
		return;
	}
	// 这里不需要复制末尾的'\0'，因为函数的最后会单独赋值
	GCString::Copy(src, size, str_out);
	size_out = size;
	gint last_no_empty = size_out - 1;
	for (last_no_empty = size_out - 1; last_no_empty >= 0; last_no_empty--)
	{
		if (str_out[last_no_empty] != ' ')
		{
			break;
		}
	}
	if (last_no_empty < 0)
	{
		size_out = 0;
		str_out[0] = '\0';
		return;
	}

	size_out = last_no_empty + 1;
	str_out[size_out] = '\0';
}

gvoid GCString::TrimRight(gcstring16 src, gsize size, gstring16 str_out, gsize &size_out)
{
	size_out = 0;
	if (size <= 0)
	{
		return;
	}
	// 这里不需要复制末尾的'\0'，因为函数的最后会单独赋值
	GCString::Copy(src, size, str_out);
	size_out = size;
	gint last_no_empty = size_out - 1;
	for (last_no_empty = size_out - 1; last_no_empty >= 0; last_no_empty--)
	{
		if (str_out[last_no_empty] != ' ')
		{
			break;
		}
	}
	if (last_no_empty < 0)
	{
		size_out = 0;
		str_out[0] = '\0';
		return;
	}

	size_out = last_no_empty + 1;
	str_out[size_out] = '\0';
}

gvoid GCString::TrimRight(gcstring32 src, gsize size, gstring32 str_out, gsize &size_out)
{
	size_out = 0;
	if (size <= 0)
	{
		return;
	}
	// 这里不需要复制末尾的'\0'，因为函数的最后会单独赋值
	GCString::Copy(src, size, str_out);
	size_out = size;
	gint last_no_empty = size_out - 1;
	for (last_no_empty = size_out - 1; last_no_empty >= 0; last_no_empty--)
	{
		if (str_out[last_no_empty] != ' ')
		{
			break;
		}
	}
	if (last_no_empty < 0)
	{
		size_out = 0;
		str_out[0] = '\0';
		return;
	}

	size_out = last_no_empty + 1;
	str_out[size_out] = '\0';
}

gvoid GCString::MakeTrim(gstring8 src, gsize size, gsize &size_out)
{
	MakeTrimLeft(src, size, size_out);
	MakeTrimRight(src, size_out, size_out);
}

gvoid GCString::MakeTrim(gstring16 src, gsize size, gsize &size_out)
{
	MakeTrimLeft(src, size, size_out);
	MakeTrimRight(src, size_out, size_out);
}

gvoid GCString::MakeTrim(gstring32 src, gsize size, gsize &size_out)
{
	MakeTrimLeft(src, size, size_out);
	MakeTrimRight(src, size_out, size_out);
}

gvoid GCString::MakeTrimLeft(gstring8 src, gsize size, gsize &size_out)
{
	size_out = 0;
	if (size <= 0)
	{
		return;
	}
	gsize first_no_empty = 0;
	for (first_no_empty = 0; first_no_empty < size; first_no_empty++)
	{
		if (src[first_no_empty] != ' ')
		{
			break;
		}
	}

	if (first_no_empty >= size)
	{
		size_out = 0;
		src[0] = '\0';
		return;
	}

	else if (first_no_empty != 0)
	{
		GMemMove(src, src + first_no_empty, size - first_no_empty);
		size_out = size - first_no_empty;
		src[size_out] = '\0';
	}
}

gvoid GCString::MakeTrimLeft(gstring16 src, gsize size, gsize &size_out)
{
	size_out = 0;
	if (size <= 0)
	{
		return;
	}
	gsize first_no_empty = 0;
	for (first_no_empty = 0; first_no_empty < size; first_no_empty++)
	{
		if (src[first_no_empty] != ' ')
		{
			break;
		}
	}

	if (first_no_empty >= size)
	{
		size_out = 0;
		src[0] = '\0';
		return;
	}

	else if (first_no_empty != 0)
	{
		GMemMove(src, src + first_no_empty, (size - first_no_empty) * 2);
		size_out = size - first_no_empty;
		src[size_out] = '\0';
	}
}

gvoid GCString::MakeTrimLeft(gstring32 src, gsize size, gsize &size_out)
{
	size_out = 0;
	if (size <= 0)
	{
		return;
	}
	gsize first_no_empty = 0;
	for (first_no_empty = 0; first_no_empty < size; first_no_empty++)
	{
		if (src[first_no_empty] != ' ')
		{
			break;
		}
	}

	if (first_no_empty >= size)
	{
		size_out = 0;
		src[0] = '\0';
		return;
	}

	else if (first_no_empty != 0)
	{
		GMemMove(src, src + first_no_empty, (size - first_no_empty) * 4);
		size_out = size - first_no_empty;
		src[size_out] = '\0';
	}
}

gvoid GCString::MakeTrimRight(gstring8 src, gsize size, gsize &size_out)
{
	size_out = size;
	if (size <= 0)
	{
		return;
	}
	gsize last_no_empty = size_out - 1;
	for (last_no_empty = size_out - 1; last_no_empty >= 0; last_no_empty--)
	{
		if (src[last_no_empty] != ' ')
		{
			break;
		}
	}

	if (last_no_empty < 0)
	{
		size_out = 0;
		src[0] = '\0';
		return;
	}

	size_out = last_no_empty + 1;
	src[size_out] = '\0';
}

gvoid GCString::MakeTrimRight(gstring16 src, gsize size, gsize &size_out)
{
	size_out = size;
	if (size <= 0)
	{
		return;
	}
	gsize last_no_empty = size_out - 1;
	for (last_no_empty = size_out - 1; last_no_empty >= 0; last_no_empty--)
	{
		if (src[last_no_empty] != ' ')
		{
			break;
		}
	}

	if (last_no_empty < 0)
	{
		size_out = 0;
		src[0] = '\0';
		return;
	}

	size_out = last_no_empty + 1;
	src[size_out] = '\0';
}

gvoid GCString::MakeTrimRight(gstring32 src, gsize size, gsize &size_out)
{
	size_out = size;
	if (size <= 0)
	{
		return;
	}
	gsize last_no_empty = size_out - 1;
	for (last_no_empty = size_out - 1; last_no_empty >= 0; last_no_empty--)
	{
		if (src[last_no_empty] != ' ')
		{
			break;
		}
	}

	if (last_no_empty < 0)
	{
		size_out = 0;
		src[0] = '\0';
		return;
	}

	size_out = last_no_empty + 1;
	src[size_out] = '\0';
}

gvoid GCString::MakeUpper(gstring8 src, gsize size)
{
	for (gsize i = 0; i < size; i++)
	{
		if (src[i] >= 'a'&&src[i] <= 'z')
		{
			src[i] -= ('a' - 'A');
		}
	}
}

gvoid GCString::MakeUpper(gstring16 src, gsize size)
{
	for (gsize i = 0; i < size; i++)
	{
		if (src[i] >= 'a'&&src[i] <= 'z')
		{
			src[i] -= ('a' - 'A');
		}
	}
}

gvoid GCString::MakeUpper(gstring32 src, gsize size)
{
	for (gsize i = 0; i < size; i++)
	{
		if (src[i] >= 'a'&&src[i] <= 'z')
		{
			src[i] -= ('a' - 'A');
		}
	}
}

gvoid GCString::MakeLower(gstring8 src, gsize size)
{
	for (gsize i = 0; i < size; i++)
	{
		if (src[i] >= 'A'&&src[i] <= 'Z')
		{
			src[i] += ('a' - 'A');
		}
	}
}

gvoid GCString::MakeLower(gstring16 src, gsize size)
{
	for (gsize i = 0; i < size; i++)
	{
		if (src[i] >= 'A'&&src[i] <= 'Z')
		{
			src[i] += ('a' - 'A');
		}
	}
}

gvoid GCString::MakeLower(gstring32 src, gsize size)
{
	for (gsize i = 0; i < size; i++)
	{
		if (src[i] >= 'A'&&src[i] <= 'Z')
		{
			src[i] += ('a' - 'A');
		}
	}
}

gint GCString::Matcher(gcstring8 src, gsize size, gchar8 ptn, gbool isSensitive)
{
	if (isSensitive)
	{
		ptn = G_CHAR_TO_LOWER(ptn);
	}
	for (gsize i = 0; i < size; ++i)
	{
		if (!isSensitive)
		{
			gchar8 _c = src[i];
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

gint GCString::Matcher(gcstring16 src, gsize size, gchar16 ptn, gbool isSensitive)
{
	if (isSensitive)
	{
		ptn = G_CHAR_TO_LOWER(ptn);
	}
	for (gsize i = 0; i < size; ++i)
	{
		if (!isSensitive)
		{
			gchar16 _c = src[i];
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

gint GCString::Matcher(gcstring32 src, gsize size, gchar32 ptn, gbool isSensitive)
{
	if (isSensitive)
	{
		ptn = G_CHAR_TO_LOWER(ptn);
	}
	for (gsize i = 0; i < size; ++i)
	{
		if (!isSensitive)
		{
			gchar32 _c = src[i];
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

gint GCString::Matcher(gcstring8 src, gsize size, gcstring8 ptn, gsize psize, gbool isSensitive)
{
	if (psize == 0)
	{
		return -1;
	}
	if (psize == 1)
	{
		return GCString::Matcher(src, size, ptn[0], isSensitive);
	}

	gsize i = 0, j = 0;
	while (j < psize && i < size) 
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
			gchar8 c1 = G_CHAR_TO_UPPER(src[i]);
			gchar8 c2 = G_CHAR_TO_UPPER(ptn[j]);
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
	if (j == psize)
		return i - psize;
	else
		return -1;
}

gint GCString::Matcher(gcstring16 src, gsize size, gcstring16 ptn, gsize psize, gbool isSensitive)
{
	if (psize == 0)
	{
		return -1;
	}
	if (psize == 1)
	{
		return GCString::Matcher(src, size, ptn[0], isSensitive);
	}

	gsize i = 0, j = 0;
	while (j < psize && i < size)
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
			gchar16 c1 = G_CHAR_TO_UPPER(src[i]);
			gchar16 c2 = G_CHAR_TO_UPPER(ptn[j]);
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
	if (j == psize)
		return i - psize;
	else
		return -1;
}

gint GCString::Matcher(gcstring32 src, gsize size, gcstring32 ptn, gsize psize, gbool isSensitive)
{
	if (psize == 0)
	{
		return -1;
	}
	if (psize == 1)
	{
		return GCString::Matcher(src, size, ptn[0], isSensitive);
	}

	gsize i = 0, j = 0;
	while (j < psize && i < size)
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
			gchar32 c1 = G_CHAR_TO_UPPER(src[i]);
			gchar32 c2 = G_CHAR_TO_UPPER(ptn[j]);
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
	if (j == psize)
		return i - psize;
	else
		return -1;
}

gbool GCString::Replace(gcstring8 src, gsize size,
	gcstring8 from, gsize from_size,
	gcstring8 to, gsize to_size,
	gbool isSensitive,
	gstring8 str_out, gsize &out_size)
{
	if (size <= 0 || from_size <= 0)
	{
		return false;
	}

	gsize start = 0;
	out_size = 0;
	for (gsize i = 0; i <= size - from_size;)
	{
		gint ret = 0;
		if (isSensitive)
		{
			ret = ::strncmp(src + i, from, from_size);
		}
		else
		{
			ret = ::strncasecmp(src + i, from, from_size);
		}
		if (ret != 0)
		{
			i++;
			continue;
		}
		if (i > start)
		{
			gsize _len_ = i - start;
			GCString::Copy(src + start, _len_, str_out + out_size);
			out_size += _len_;
		}
		GCString::Copy(to, to_size, str_out + out_size);
		out_size += to_size;
		i += from_size;
		start = i;
	}
	if (start <= 0)
	{
		return false;
	}
	gsize _len_ = size - start;
	GCString::Copy(src + start, _len_, str_out + out_size);
	out_size += _len_;
	str_out[out_size] = '\0';
	return true;
}

} // namespace gsystem
