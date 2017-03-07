#include "gcstringhelper.h"
#include "gmemory.h"
#include <string>
#include <string.h>


#ifdef _MSC_VER
#	ifndef G_USE_MSVC_STRCMP
gint strcasecmp(const gchar *s1, gchar *s2)
{
	while (toupper((guchar)*s1) == toupper((guchar)*s2++))
		if (*s1++ == '\0') return 0;
	return(toupper((guchar)*s1) - toupper((guchar)*--s2));
}

int strncasecmp(const gchar *s1, gchar *s2, /*register*/ gint n)
{
	while (--n >= 0 && toupper((guchar)*s1) == toupper((guchar)*s2++))
		if (*s1++ == '\0')  return 0;
	return(n < 0 ? 0 : toupper((guchar)*s1) - toupper((guchar)*--s2));
}
#	endif // !G_USE_MSVC_STRCMP
#endif


gsize GCStringHelper::Size(const gchar *c_str)
{
	if (GNULL == c_str)
	{
		return 0;
	}
	return strlen(c_str);
}

gvoid GCStringHelper::Copy(const gchar *src, gsize len, gchar *dest)
{
	GMemCopy(dest, src, len);
}

gvoid GCStringHelper::Trim(const gchar *c_str, gsize size,
	gchar *out_c_str, gsize &out_size)
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
	GCStringHelper::Copy(c_str + first_no_empty, size - first_no_empty, out_c_str);
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

gvoid GCStringHelper::TrimLeft(const gchar *c_str, gsize size,
	gchar *out_c_str, gsize &out_size)
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
	GCStringHelper::Copy(c_str + first_no_empty, size - first_no_empty, out_c_str);
	out_size = size - first_no_empty;
	out_c_str[out_size] = '\0';
}

gvoid GCStringHelper::TrimRight(const gchar *c_str, gsize size,
	gchar *out_c_str, gsize &out_size)
{
	out_size = 0;
	if (size <= 0)
	{
		return;
	}
	// 这里不需要复制末尾的'\0'，因为函数的最后会单独赋值
	GCStringHelper::Copy(c_str, size, out_c_str);
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

gvoid GCStringHelper::MakeTrim(gchar *c_str, gsize size, gsize &out_size)
{
	MakeTrimLeft(c_str, size, out_size);
	MakeTrimRight(c_str, out_size, out_size);
}

gvoid GCStringHelper::MakeTrimLeft(gchar *c_str, gsize size, gsize &out_size)
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
		memmove(c_str, c_str + first_no_empty, size - first_no_empty);
		out_size = size - first_no_empty;
		c_str[out_size] = '\0';
	}
}

gvoid GCStringHelper::MakeTrimRight(gchar *c_str, gsize size, gsize &out_size)
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

gvoid GCStringHelper::MakeUpper(gchar *c_str, gsize size)
{
	for (gsize i = 0; i < size; i++)
	{
		if (c_str[i] >= 'a'&&c_str[i] <= 'z')
		{
			c_str[i] -= ('a' - 'A');
		}
	}
}

gvoid GCStringHelper::MakeLower(gchar *c_str, gsize size)
{
	for (gsize i = 0; i < size; i++)
	{
		if (c_str[i] >= 'A'&&c_str[i] <= 'Z')
		{
			c_str[i] += ('a' - 'A');
		}
	}
}

gbool GCStringHelper::Replace(const gchar *c_str, gsize len, 
	const gchar *from, gsize from_len,
	const gchar *to, gsize to_len,
	gbool bIsSensitive,
	gchar *c_str_out, gsize &out_len)
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
		if (bIsSensitive)
		{
			ret = strncmp(c_str + i, from, from_len);
		}
		else
		{
			ret = strncasecmp(c_str + i, from, from_len);
		}
		if (ret != 0)
		{
			i++;
			continue;
		}
		if (i > start)
		{
			gsize _len_ = i - start;
			GCStringHelper::Copy(c_str + start, _len_, c_str_out + out_len);
			out_len += _len_;
		}
		GCStringHelper::Copy(to, to_len, c_str_out + out_len);
		out_len += to_len;
		i += from_len;
		start = i;
	}
	if (start <= 0)
	{
		return false;
	}
	gsize _len_ = len - start;
	GCStringHelper::Copy(c_str + start, _len_, c_str_out + out_len);
	out_len += _len_;
	c_str_out[out_len] = '\0';
	return true;
}
