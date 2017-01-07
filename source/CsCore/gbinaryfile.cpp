#include "gbinaryfile.h"
#include "CsBinaryFile_Ex.h"

GBinaryFile::GBinaryFile(const GString &sFileName)
: GFile(new CsBinaryFile_Ex(sFileName))
{

}

GBinaryFile::GBinaryFile(CsBinaryFile_Ex *pBinaryFile_Ex)
: GFile(pBinaryFile_Ex)
{

}

gbool GBinaryFile::Read(gsize size, GBytes &bytes)
{
	if (!m_pFileEx)
	{
		return false;
	}
	CsBinaryFile_Ex *m_pBinaryFile_Ex = (CsBinaryFile_Ex*)m_pFileEx;
	return m_pBinaryFile_Ex->Read(size, bytes);
}

gbool GBinaryFile::ReadAll(GBytes &bytes)
{
	if (!m_pFileEx)
	{
		return false;
	}
	CsBinaryFile_Ex *m_pBinaryFile_Ex = (CsBinaryFile_Ex*)m_pFileEx;
	return m_pBinaryFile_Ex->ReadAll(bytes);
}

gbool GBinaryFile::Write(const GBytes &bytes)
{
	if (!m_pFileEx)
	{
		return false;
	}
	CsBinaryFile_Ex *m_pBinaryFile_Ex = (CsBinaryFile_Ex*)m_pFileEx;
	return m_pBinaryFile_Ex->Write(bytes);
}
