#include "CsFile_Ex.h"
#include "gstring.h"
#include "gfile.h"

CsFile_Ex::CsFile_Ex(const GString &sFileName)
: m_sFileName(sFileName)
, m_pFileStream(NULL)
, m_nOpenMode(GFile::NO_OPEN)
{

}

CsFile_Ex::~CsFile_Ex()
{
	Close();
}

gbool CsFile_Ex::Valid() const
{
	return m_pFileStream != NULL;
}

gbool CsFile_Ex::EndOfFile() const
{
	if (!m_pFileStream)
	{
		return true;
	}
	return feof(m_pFileStream);
}

const GString &CsFile_Ex::FileName() const
{
	return m_sFileName;
}

GString &CsFile_Ex::FileName()
{
	return m_sFileName;
}

gvoid CsFile_Ex::SetFileName(const GString &sFileName)
{
	m_sFileName = sFileName;
}

gbool CsFile_Ex::Open(gbyte nOpenMode)
{
	if (m_sFileName.IsEmpty() || 
		nOpenMode == GFile::NO_OPEN)
	{
		return false;
	}
	
	m_nOpenMode = nOpenMode;
	gcstring open_mode = OpenMode();
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

gvoid CsFile_Ex::Flush()
{
	if (m_pFileStream)
	{
		fflush(m_pFileStream);
	}
}

gvoid CsFile_Ex::Close()
{
	if (m_pFileStream)
	{
		fflush(m_pFileStream);
		fclose(m_pFileStream);
	}
}

gbool CsFile_Ex::Seek(glong offset, gbyte mode)
{
	if (!Valid())
	{
		return false;
	}
	switch (mode)
	{
	case GFile::SEEK_MODE_START:
		return fseek(m_pFileStream, offset, SEEK_SET) == 0;
		break;
	case GFile::SEEK_MODE_CURRENT:
		return fseek(m_pFileStream, offset, SEEK_CUR) == 0;
		break;
	case GFile::SEEK_MODE_END:
		return fseek(m_pFileStream, offset, SEEK_END) == 0;
		break;
	default:
		break;
	}
	return false;
}

glong CsFile_Ex::Tell() const
{
	if (!Valid())
	{
		return -1;
	}
	return ftell(m_pFileStream);
}

gvoid CsFile_Ex::Rewind()
{
	if (Valid())
	{
		rewind(m_pFileStream);
	}
}

gbool CsFile_Ex::CanRead() const
{
	if (m_nOpenMode == GFile::NO_OPEN ||
		m_nOpenMode == GFile::ONLY_WIRTE)
	{
		return false;
	}
	return true;
}

gbool CsFile_Ex::CanWrite() const
{
	if (m_nOpenMode == GFile::NO_OPEN ||
		m_nOpenMode == GFile::ONLY_READ)
	{
		return false;
	}
	return true;
}
