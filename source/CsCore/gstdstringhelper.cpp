#include "gstdstringhelper.h"

std::string GStdStringHelper::Trim(const std::string &sStr)
{
	std::string _sStr(sStr);
	std::string::size_type pos = _sStr.find_last_not_of(' ');
	if (pos != std::string::npos)
	{
		_sStr.erase(pos + 1);
		pos = _sStr.find_first_not_of(' ');
		if (pos != std::string::npos) _sStr.erase(0, pos);
	}
	else
	{
		_sStr.erase(_sStr.begin(), _sStr.end());
	}
	return _sStr;
}

std::string GStdStringHelper::ToUpper(const std::string &sStr)
{
	std::string _sStr;
	std::string::size_type i = 0;
	std::string::size_type end = sStr.size();
	for (i = 0; i < end; i++)
	{
		gchar c = toupper(sStr.at(i));
		_sStr.push_back(c);
	}
	return _sStr;
}

std::string GStdStringHelper::ToLower(const std::string &sStr)
{
	std::string _sStr;
	std::string::size_type i = 0;
	std::string::size_type end = sStr.size();
	for (i = 0; i < end; i++)
	{
		gchar c = tolower(sStr.at(i));
		_sStr.push_back(c);
	}
	return _sStr;
}

std::string GStdStringHelper::Replace(const std::string &sStr, const std::string &from,
	const std::string &to, gbool bIsSensitive)
{
	std::string _sStr(sStr);
	if (bIsSensitive)
	{
		std::string::size_type fromLen = from.size();
		std::string::size_type toLen = to.size();
		std::string::size_type pos = _sStr.find(from, 0);
		while (pos != std::string::npos)
		{
			_sStr.replace(pos, fromLen, to);
			pos = _sStr.find(from, pos + toLen);
		}
	}
	else
	{
		std::string _sStr_Upper = ToUpper(_sStr);
		std::string _from = ToUpper(from);
		std::string::size_type fromLen = _from.size();
		std::string::size_type toLen = to.size();
		std::string::size_type pos = _sStr_Upper.find(_from, 0);
		while (pos != std::string::npos)
		{
			_sStr_Upper.replace(pos, fromLen, to);
			_sStr.replace(pos, fromLen, to);
			pos = _sStr_Upper.find(_from, pos + toLen);
		}
	}
	return _sStr;
}

gvoid GStdStringHelper::Split(const std::string &sStr, const std::string &sSep,
	gbool bIgnoreEmpty, gbool bIsSensitive,
	std::vector<std::string> &tStrs)
{
	std::string _sSep(sSep);
	if (_sSep.empty())
	{
		return;
	}

	std::string _sStr(sStr);
	if (!bIsSensitive)
	{
		// 大小写不敏感
		_sSep = ToUpper(_sSep);
		_sStr = ToUpper(_sStr);
	}
	_sStr += _sSep; // 扩展字符串以方便操作

	std::string::size_type nPos;
	gsize nSize = _sStr.size();
	for (gsize i = 0; i < nSize; i++)
	{
		nPos = _sStr.find(_sSep, i);
		if (nPos < nSize)
		{
			if (bIgnoreEmpty)
			{
				// 忽略空格
				std::string sRes = Trim(sStr.substr(i, nPos - i));
				if (!sRes.empty())
				{
					tStrs.push_back(sRes);
				}
			}
			else
			{
				tStrs.push_back(sStr.substr(i, nPos - i));
			}
			i = nPos + _sSep.size() - 1;
		}
	}
}

gint GStdStringHelper::Find(const std::string &str, gchar c, gsize start, gbool bIsSensitive)
{
	std::string::size_type pos = std::string::npos;
	if (bIsSensitive)
	{
		pos = str.find(c, start);
	}
	else
	{
		std::string _str = ToUpper(str);
		gchar _c = toupper(c);
		pos = _str.find(_c, start);
	}
	if (pos == std::string::npos)
	{
		return -1;
	}
	return static_cast<gint>(pos);
}

gint GStdStringHelper::Find(const std::string &str, const std::string &tar, gsize start, gbool bIsSensitive)
{
	std::string::size_type pos = std::string::npos;
	if (bIsSensitive)
	{
		pos = str.find(tar, start);
	}
	else
	{
		std::string _str = ToUpper(str);
		std::string _tar = ToUpper(tar);
		pos = _str.find(_tar, start);
	}
	if (pos == std::string::npos)
	{
		return -1;
	}
	return static_cast<gint>(pos);
}
