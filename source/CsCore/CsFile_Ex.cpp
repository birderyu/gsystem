#include "CsFile_Ex.h"
#include "CsString.h"
#include "CsFile.h"

CsFile_Ex::CsFile_Ex(const CsString &sFileName)
: m_sFileName(sFileName)
, m_pFileStream(NULL)
, m_nOpenMode(CsFile::NO_OPEN)
{

}

CsFile_Ex::~CsFile_Ex()
{
	Close();
}

cs_bool CsFile_Ex::Valid() const
{
	return m_pFileStream != NULL;
}

cs_bool CsFile_Ex::EndOfFile() const
{
	if (!m_pFileStream)
	{
		return true;
	}
	return feof(m_pFileStream);
}

const CsString &CsFile_Ex::FileName() const
{
	return m_sFileName;
}

CsString &CsFile_Ex::FileName()
{
	return m_sFileName;
}

cs_void CsFile_Ex::SetFileName(const CsString &sFileName)
{
	m_sFileName = sFileName;
}

cs_bool CsFile_Ex::Open(cs_byte nOpenMode)
{
	if (m_sFileName.IsEmpty() || 
		nOpenMode == CsFile::NO_OPEN)
	{
		return false;
	}
	
	m_nOpenMode = nOpenMode;
	cs_cstring open_mode = OpenMode();
	if (!open_mode)
	{
		return false;
	}

	FILE *new_file_stream = NULL;
	errno_t errno;
	errno = fopen_s(&new_file_stream, m_sFileName.CString(), open_mode);
	if (!new_file_stream || errno != 0)
	{
		return false;
	}

	// 关闭旧的文件流
	Close();
	m_pFileStream = new_file_stream;
	return true;
}

cs_void CsFile_Ex::Flush()
{
	if (m_pFileStream)
	{
		fflush(m_pFileStream);
	}
}

cs_void CsFile_Ex::Close()
{
	if (m_pFileStream)
	{
		fflush(m_pFileStream);
		fclose(m_pFileStream);
	}
}

cs_bool CsFile_Ex::Seek(cs_long offset, cs_byte mode)
{
	if (!Valid())
	{
		return false;
	}
	switch (mode)
	{
	case CsFile::SEEK_MODE_START:
		return fseek(m_pFileStream, offset, SEEK_SET) == 0;
		break;
	case CsFile::SEEK_MODE_CURRENT:
		return fseek(m_pFileStream, offset, SEEK_CUR) == 0;
		break;
	case CsFile::SEEK_MODE_END:
		return fseek(m_pFileStream, offset, SEEK_END) == 0;
		break;
	default:
		break;
	}
	return false;
}

cs_long CsFile_Ex::Tell() const
{
	if (!Valid())
	{
		return -1;
	}
	return ftell(m_pFileStream);
}

cs_void CsFile_Ex::Rewind()
{
	if (Valid())
	{
		rewind(m_pFileStream);
	}
}

cs_bool CsFile_Ex::CanRead() const
{
	if (m_nOpenMode == CsFile::NO_OPEN ||
		m_nOpenMode == CsFile::ONLY_WIRTE)
	{
		return false;
	}
	return true;
}

cs_bool CsFile_Ex::CanWrite() const
{
	if (m_nOpenMode == CsFile::NO_OPEN ||
		m_nOpenMode == CsFile::ONLY_READ)
	{
		return false;
	}
	return true;
}
