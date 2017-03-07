#include "gfile_ex.h"
#include "gstring.h"
#include "gfile.h"

GFile_Ex::GFile_Ex(const GString &sFileName)
: m_sFileName(sFileName)
, m_pFileStream(GNULL)
, m_nOpenMode(GFile::NO_OPEN)
{

}

GFile_Ex::~GFile_Ex()
{
	Close();
}

gbool GFile_Ex::Valid() const
{
	return m_pFileStream != GNULL;
}

gbool GFile_Ex::EndOfFile() const
{
	if (!m_pFileStream)
	{
		return true;
	}
	return feof(m_pFileStream) != 0;
}

const GString &GFile_Ex::FileName() const
{
	return m_sFileName;
}

GString &GFile_Ex::FileName()
{
	return m_sFileName;
}

gvoid GFile_Ex::SetFileName(const GString &sFileName)
{
	m_sFileName = sFileName;
}

gbool GFile_Ex::Open(gbyte nOpenMode)
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

	FILE *new_file_stream = GNULL;
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

gvoid GFile_Ex::Flush()
{
	if (m_pFileStream)
	{
		fflush(m_pFileStream);
	}
}

gvoid GFile_Ex::Close()
{
	if (m_pFileStream)
	{
		fflush(m_pFileStream);
		fclose(m_pFileStream);
	}
}

gbool GFile_Ex::Seek(glong offset, gbyte mode)
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

glong GFile_Ex::Tell() const
{
	if (!Valid())
	{
		return -1;
	}
	return ftell(m_pFileStream);
}

gvoid GFile_Ex::Rewind()
{
	if (Valid())
	{
		rewind(m_pFileStream);
	}
}

gbool GFile_Ex::CanRead() const
{
	if (m_nOpenMode == GFile::NO_OPEN ||
		m_nOpenMode == GFile::ONLY_WIRTE)
	{
		return false;
	}
	return true;
}

gbool GFile_Ex::CanWrite() const
{
	if (m_nOpenMode == GFile::NO_OPEN ||
		m_nOpenMode == GFile::ONLY_READ)
	{
		return false;
	}
	return true;
}
