#include "gcstringhelper.h"
#include "gnew.h"
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
	return strlen(c_str);
}

gbool GCStringHelper::Copy(const gchar *src, gsize len, gchar *dest)
{
	GMemCopy(dest, src, len);
	return true;
}

gbool GCStringHelper::Trim(const gchar *c_str, gsize len,
	gchar *c_str_out, gsize &len_out)
{
	len_out = 0;
	if (len <= 0)
	{
		return true;
	}
	gsize first_no_empty = 0;
	for (first_no_empty = 0; first_no_empty < len; first_no_empty++)
	{
		if (c_str[first_no_empty] != ' ')
		{
			break;
		}
	}
	if (first_no_empty >= len)
	{
		len_out = 0;
		c_str_out[0] = '\0';
		return true;
	}

	// 这里不需要复制末尾的'\0'，因为函数的最后会单独赋值
	GCStringHelper::Copy(c_str + first_no_empty, len - first_no_empty, c_str_out);
	len_out = len - first_no_empty;

	gint last_no_empty = len_out - 1;
	for (last_no_empty = len_out - 1; last_no_empty >= 0; last_no_empty--)
	{
		if (c_str_out[last_no_empty] != ' ')
		{
			break;
		}
	}
	if (last_no_empty < 0)
	{
		len_out = 0;
		c_str_out[0] = '\0';
		return true;
	}

	len_out = last_no_empty + 1;
	c_str_out[len_out] = '\0';
	return true;
}

gbool GCStringHelper::TrimLeft(const gchar *c_str, gsize len,
	gchar *c_str_out, gsize &len_out)
{
	len_out = 0;
	if (len <= 0)
	{
		return true;
	}
	gsize first_no_empty = 0;
	for (first_no_empty = 0; first_no_empty < len; first_no_empty++)
	{
		if (c_str[first_no_empty] != ' ')
		{
			break;
		}
	}
	if (first_no_empty >= len)
	{
		len_out = 0;
		c_str_out[0] = '\0';
		return true;
	}

	// 这里不需要复制末尾的'\0'，因为函数的最后会单独赋值
	GCStringHelper::Copy(c_str + first_no_empty, len - first_no_empty, c_str_out);
	len_out = len - first_no_empty;
	c_str_out[len_out] = '\0';
	return true;
}

gbool GCStringHelper::TrimRight(const gchar *c_str, gsize len,
	gchar *c_str_out, gsize &len_out)
{
	len_out = 0;
	if (len <= 0)
	{
		return true;
	}
	// 这里不需要复制末尾的'\0'，因为函数的最后会单独赋值
	GCStringHelper::Copy(c_str, len, c_str_out);
	len_out = len;
	gint last_no_empty = len_out - 1;
	for (last_no_empty = len_out - 1; last_no_empty >= 0; last_no_empty--)
	{
		if (c_str_out[last_no_empty] != ' ')
		{
			break;
		}
	}
	if (last_no_empty < 0)
	{
		len_out = 0;
		c_str_out[0] = '\0';
		return true;
	}

	len_out = last_no_empty + 1;
	c_str_out[len_out] = '\0';
	return true;
}

gbool GCStringHelper::MakeTrim(gchar *c_str, gsize len, gsize &len_out)
{
	return MakeTrimLeft(c_str, len, len_out) &&
		MakeTrimRight(c_str, len_out, len_out);
}

gbool GCStringHelper::MakeTrimLeft(gchar *c_str, gsize len, gsize &len_out)
{
	len_out = 0;
	if (len <= 0)
	{
		return true;
	}
	gsize first_no_empty = 0;
	for (first_no_empty = 0; first_no_empty < len; first_no_empty++)
	{
		if (c_str[first_no_empty] != ' ')
		{
			break;
		}
	}

	if (first_no_empty >= len)
	{
		len_out = 0;
		c_str[0] = '\0';
		return true;
	}
	else if (first_no_empty != 0)
	{
		memmove(c_str, c_str + first_no_empty, len - first_no_empty);
		len_out = len - first_no_empty;
		c_str[len_out] = '\0';
	}
	return true;
}

gbool GCStringHelper::MakeTrimRight(gchar *c_str, gsize len, gsize &len_out)
{
	len_out = len;
	if (len <= 0)
	{
		return true;
	}
	gsize last_no_empty = len_out - 1;
	for (last_no_empty = len_out - 1; last_no_empty >= 0; last_no_empty--)
	{
		if (c_str[last_no_empty] != ' ')
		{
			break;
		}
	}

	if (last_no_empty < 0)
	{
		len_out = 0;
		c_str[0] = '\0';
		return true;
	}

	len_out = last_no_empty + 1;
	c_str[len_out] = '\0';
	return true;
}

gbool GCStringHelper::MakeUpper(gchar *c_str, gsize len)
{
	for (gsize i = 0; i < len; i++)
	{
		if (c_str[i] >= 'a'&&c_str[i] <= 'z')
		{
			c_str[i] -= ('a' - 'A');
		}
	}
	return true;
}

gbool GCStringHelper::MakeLower(gchar *c_str, gsize len)
{
	for (gsize i = 0; i < len; i++)
	{
		if (c_str[i] >= 'A'&&c_str[i] <= 'Z')
		{
			c_str[i] += ('a' - 'A');
		}
	}
	return true;
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
