#include "CsTextFile_Ex.h"
#include "CsTextFile.h"

#define CS_TEXT_DOCUMNET_BUFFER_SIZE 4096

CsTextFile_Ex::CsTextFile_Ex(const CsString &sFileName)
: CsFile_Ex(sFileName)
{

}

cs_byte CsTextFile_Ex::Format() const
{
	return CsFile::TEXT_FILE;
}

cs_bool CsTextFile_Ex::GetChar(cs_uchar &c)
{
	if (EndOfFile() || !CanRead())
	{
		return false;
	}

	cs_int ic = fgetc(m_pFileStream);
	if (EOF == ic)
	{
		return false;
	}

	c = static_cast<cs_uchar>(ic);
	return true;
}

cs_bool CsTextFile_Ex::PutChar(cs_uchar c)
{
	if (!Valid() || !CanWrite())
	{
		return false;
	}

	if (EOF == fputc(c, m_pFileStream))
	{
		return false;
	}
	return false;
}

cs_bool CsTextFile_Ex::Read(cs_size_t size, CsString &str)
{
	if (EndOfFile() || !CanRead() || size <= 0)
	{
		return false;
	}

	cs_size_t old_size = str.Size();
	if (!str.Resize(old_size + size))
	{
		return false;
	}
	cs_cstring c = fgets(str.Cursor(old_size), size + 1, m_pFileStream);
	if (c == NULL)
	{
		str.Resize(old_size);
		return false;
	}

	return true;
}

cs_bool CsTextFile_Ex::ReadAll(CsString &str)
{
	if (!Valid() || !CanRead())
	{
		return false;
	}

	// 旧的文件游标备份
	cs_long old_tell = Tell();

	if (!Seek(0, CsFile::SEEK_MODE_END))
	{
		// 还原游标
		Seek(old_tell, CsFile::SEEK_MODE_START);
		return false;
	}

	cs_long all_size = Tell();
	if (all_size < 0)
	{
		// 还原游标
		Seek(old_tell, CsFile::SEEK_MODE_START);
		return false;
	}

	// 将游标设置到初始位置
	Rewind();
	if (!Read(all_size, str))
	{
		// 还原游标
		Seek(old_tell, CsFile::SEEK_MODE_START);
		return false;
	}

	return true;
}

cs_bool CsTextFile_Ex::Write(const CsString &str)
{
	if (!Valid() || !CanWrite())
	{
		return false;
	}

	if (EOF == fputs(str.CString(), m_pFileStream))
	{
		return false;
	}
	return false;
}

cs_cstring CsTextFile_Ex::OpenMode() const
{
	switch (m_nOpenMode)
	{
	case CsFile::NO_OPEN:
		return NULL;
	case CsFile::ONLY_READ:
		return "rt";
	case CsFile::ONLY_WIRTE:
		return "wt";
	case CsFile::READ_WIRTE:
		return "rt+";
	case CsFile::APPEND:
		return "at";
	default:
		break;
	}
	return NULL;
}

#undef CS_TEXT_DOCUMNET_BUFFER_SIZE
