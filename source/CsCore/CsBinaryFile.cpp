#include "CsBinaryFile.h"
#include "CsBinaryFile_Ex.h"

CsBinaryFile::CsBinaryFile(const CsString &sFileName)
: CsFile(new CsBinaryFile_Ex(sFileName))
{

}

CsBinaryFile::CsBinaryFile(CsBinaryFile_Ex *pBinaryFile_Ex)
: CsFile(pBinaryFile_Ex)
{

}

cs_bool CsBinaryFile::Read(cs_size_t size, CsBytes &bytes)
{
	if (!m_pFileEx)
	{
		return false;
	}
	CsBinaryFile_Ex *m_pBinaryFile_Ex = (CsBinaryFile_Ex*)m_pFileEx;
	return m_pBinaryFile_Ex->Read(size, bytes);
}

cs_bool CsBinaryFile::ReadAll(CsBytes &bytes)
{
	if (!m_pFileEx)
	{
		return false;
	}
	CsBinaryFile_Ex *m_pBinaryFile_Ex = (CsBinaryFile_Ex*)m_pFileEx;
	return m_pBinaryFile_Ex->ReadAll(bytes);
}

cs_bool CsBinaryFile::Write(const CsBytes &bytes)
{
	if (!m_pFileEx)
	{
		return false;
	}
	CsBinaryFile_Ex *m_pBinaryFile_Ex = (CsBinaryFile_Ex*)m_pFileEx;
	return m_pBinaryFile_Ex->Write(bytes);
}
