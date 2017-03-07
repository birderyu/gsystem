#include "gfile.h"
#include "gfile_ex.h"

GFile::GFile(GFile_Ex *pFile_Ex)
: m_pFileEx(pFile_Ex)
{

}

GFile::~GFile()
{
	if (m_pFileEx)
	{
		delete m_pFileEx;
	}
}

GFile::FILE_FORMAT GFile::Format() const
{
	GASSERT(m_pFileEx);
	return (GFile::FILE_FORMAT)m_pFileEx->Format();
}

gbool GFile::Valid() const
{
	GASSERT(m_pFileEx);
	return m_pFileEx->Valid();
}

gbool GFile::EndOfFile() const
{
	GASSERT(m_pFileEx);
	return m_pFileEx->EndOfFile();
}

const GString &GFile::FileName() const
{
	GASSERT(m_pFileEx);
	return m_pFileEx->FileName();
}

GString &GFile::FileName()
{
	GASSERT(m_pFileEx);
	return m_pFileEx->FileName();
}

gvoid GFile::SetFileName(const GString &sFileName)
{
	GASSERT(m_pFileEx);
	m_pFileEx->SetFileName(sFileName);
}

gbool GFile::Open(OPEN_MODE emOpenMode)
{
	GASSERT(m_pFileEx);
	return m_pFileEx->Open(emOpenMode);
}

gvoid GFile::Close()
{
	GASSERT(m_pFileEx);
	m_pFileEx->Close();
}

gbool GFile::Seek(glong offset, SEEK_MODE mode)
{
	GASSERT(m_pFileEx);
	return m_pFileEx->Seek(offset, mode);
}

glong GFile::Tell() const
{
	GASSERT(m_pFileEx);
	return m_pFileEx->Tell();
}

gvoid GFile::Rewind()
{
	GASSERT(m_pFileEx);
	m_pFileEx->Rewind();
}

gsize GFile::Size() const
{
	glong size = Tell();
	if (size < 0)
	{
		return 0;
	}
	return static_cast<gsize>(size);
}
