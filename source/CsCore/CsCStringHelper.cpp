#include "CsCStringHelper.h"
#include <string>
#include <string.h>


#ifdef _MSC_VER
#	ifndef CS_USE_MSVC_STRCMP
cs_int strcasecmp(const cs_char *s1, cs_char *s2)
{
	while (toupper((cs_uchar)*s1) == toupper((cs_uchar)*s2++))
		if (*s1++ == '\0') return 0;
	return(toupper((cs_uchar)*s1) - toupper((cs_uchar)*--s2));
}

int strncasecmp(const cs_char *s1, cs_char *s2, /*register*/ cs_int n)
{
	while (--n >= 0 && toupper((cs_uchar)*s1) == toupper((cs_uchar)*s2++))
		if (*s1++ == '\0')  return 0;
	return(n < 0 ? 0 : toupper((cs_uchar)*s1) - toupper((cs_uchar)*--s2));
}
#	endif
#endif


cs_size_t CsCStringHelper::Length(const cs_char *c_str)
{
	return strlen(c_str);
}

cs_bool CsCStringHelper::Copy(const cs_char *src, cs_size_t len, cs_char *dest)
{
	memcpy(dest, src, len);
	return true;
}

cs_bool CsCStringHelper::Trim(const cs_char *c_str, cs_size_t len,
	cs_char *c_str_out, cs_size_t &len_out)
{
	len_out = 0;
	if (len <= 0)
	{
		return true;
	}
	cs_size_t first_no_empty = 0;
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
	CsCStringHelper::Copy(c_str + first_no_empty, len - first_no_empty, c_str_out);
	len_out = len - first_no_empty;

	cs_int last_no_empty = len_out - 1;
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

cs_bool CsCStringHelper::TrimLeft(const cs_char *c_str, cs_size_t len,
	cs_char *c_str_out, cs_size_t &len_out)
{
	len_out = 0;
	if (len <= 0)
	{
		return true;
	}
	cs_size_t first_no_empty = 0;
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
	CsCStringHelper::Copy(c_str + first_no_empty, len - first_no_empty, c_str_out);
	len_out = len - first_no_empty;
	c_str_out[len_out] = '\0';
	return true;
}

cs_bool CsCStringHelper::TrimRight(const cs_char *c_str, cs_size_t len,
	cs_char *c_str_out, cs_size_t &len_out)
{
	len_out = 0;
	if (len <= 0)
	{
		return true;
	}
	// 这里不需要复制末尾的'\0'，因为函数的最后会单独赋值
	CsCStringHelper::Copy(c_str, len, c_str_out);
	len_out = len;
	cs_int last_no_empty = len_out - 1;
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

cs_bool CsCStringHelper::MakeTrim(cs_char *c_str, cs_size_t len, cs_size_t &len_out)
{
	return MakeTrimLeft(c_str, len, len_out) &&
		MakeTrimRight(c_str, len_out, len_out);
}

cs_bool CsCStringHelper::MakeTrimLeft(cs_char *c_str, cs_size_t len, cs_size_t &len_out)
{
	len_out = 0;
	if (len <= 0)
	{
		return true;
	}
	cs_size_t first_no_empty = 0;
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

cs_bool CsCStringHelper::MakeTrimRight(cs_char *c_str, cs_size_t len, cs_size_t &len_out)
{
	len_out = len;
	if (len <= 0)
	{
		return true;
	}
	cs_size_t last_no_empty = len_out - 1;
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

cs_bool CsCStringHelper::MakeUpper(cs_char *c_str, cs_size_t len)
{
	for (cs_size_t i = 0; i < len; i++)
	{
		if (c_str[i] >= 'a'&&c_str[i] <= 'z')
		{
			c_str[i] -= ('a' - 'A');
		}
	}
	return true;
}

cs_bool CsCStringHelper::MakeLower(cs_char *c_str, cs_size_t len)
{
	for (cs_size_t i = 0; i < len; i++)
	{
		if (c_str[i] >= 'A'&&c_str[i] <= 'Z')
		{
			c_str[i] += ('a' - 'A');
		}
	}
	return true;
}

cs_bool CsCStringHelper::Replace(const cs_char *c_str, cs_size_t len, 
	const cs_char *from, cs_size_t from_len,
	const cs_char *to, cs_size_t to_len,
	cs_bool bIsSensitive,
	cs_char *c_str_out, cs_size_t &out_len)
{
	if (len <= 0 || from_len <= 0)
	{
		return false;
	}

	cs_size_t start = 0;
	out_len = 0;
	for (cs_size_t i = 0; i <= len - from_len;)
	{
		cs_int ret = 0;
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
			cs_size_t _len_ = i - start;
			CsCStringHelper::Copy(c_str + start, _len_, c_str_out + out_len);
			out_len += _len_;
		}
		CsCStringHelper::Copy(to, to_len, c_str_out + out_len);
		out_len += to_len;
		i += from_len;
		start = i;
	}
	if (start <= 0)
	{
		return false;
	}
	cs_size_t _len_ = len - start;
	CsCStringHelper::Copy(c_str + start, _len_, c_str_out + out_len);
	out_len += _len_;
	c_str_out[out_len] = '\0';
	return true;
}
