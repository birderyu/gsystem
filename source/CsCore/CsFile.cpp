#include "CsFile.h"
#include "CsFile_Ex.h"

CsFile::CsFile(CsFile_Ex *pFile_Ex)
: m_pFileEx(pFile_Ex)
{

}

CsFile::~CsFile()
{
	if (m_pFileEx)
	{
		delete m_pFileEx;
	}
}

CsFile::FILE_FORMAT CsFile::Format() const
{
	CS_ASSERT(m_pFileEx);
	return (CsFile::FILE_FORMAT)m_pFileEx->Format();
}

cs_bool CsFile::Valid() const
{
	CS_ASSERT(m_pFileEx);
	return m_pFileEx->Valid();
}

cs_bool CsFile::EndOfFile() const
{
	CS_ASSERT(m_pFileEx);
	return m_pFileEx->EndOfFile();
}

const CsString &CsFile::FileName() const
{
	CS_ASSERT(m_pFileEx);
	return m_pFileEx->FileName();
}

CsString &CsFile::FileName()
{
	CS_ASSERT(m_pFileEx);
	return m_pFileEx->FileName();
}

cs_void CsFile::SetFileName(const CsString &sFileName)
{
	CS_ASSERT(m_pFileEx);
	m_pFileEx->SetFileName(sFileName);
}

cs_bool CsFile::Open(OPEN_MODE emOpenMode)
{
	CS_ASSERT(m_pFileEx);
	return m_pFileEx->Open(emOpenMode);
}

cs_void CsFile::Close()
{
	CS_ASSERT(m_pFileEx);
	m_pFileEx->Close();
}

cs_bool CsFile::Seek(cs_long offset, SEEK_MODE mode)
{
	CS_ASSERT(m_pFileEx);
	return m_pFileEx->Seek(offset, mode);
}

cs_long CsFile::Tell() const
{
	CS_ASSERT(m_pFileEx);
	return m_pFileEx->Tell();
}

cs_void CsFile::Rewind()
{
	CS_ASSERT(m_pFileEx);
	m_pFileEx->Rewind();
}
