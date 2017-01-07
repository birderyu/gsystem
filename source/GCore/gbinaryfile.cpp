#include "gbinaryfile.h"
#include "gbinaryfile_ex.h"

GBinaryFile::GBinaryFile(const GString &sFileName)
: GFile(new GBinaryFile_Ex(sFileName))
{

}

GBinaryFile::GBinaryFile(GBinaryFile_Ex *pBinaryFile_Ex)
: GFile(pBinaryFile_Ex)
{

}

gbool GBinaryFile::Read(gsize size, GBytes &bytes)
{
	if (!m_pFileEx)
	{
		return false;
	}
	GBinaryFile_Ex *m_pBinaryFile_Ex = (GBinaryFile_Ex*)m_pFileEx;
	return m_pBinaryFile_Ex->Read(size, bytes);
}

gbool GBinaryFile::ReadAll(GBytes &bytes)
{
	if (!m_pFileEx)
	{
		return false;
	}
	GBinaryFile_Ex *m_pBinaryFile_Ex = (GBinaryFile_Ex*)m_pFileEx;
	return m_pBinaryFile_Ex->ReadAll(bytes);
}

gbool GBinaryFile::Write(const GBytes &bytes)
{
	if (!m_pFileEx)
	{
		return false;
	}
	GBinaryFile_Ex *m_pBinaryFile_Ex = (GBinaryFile_Ex*)m_pFileEx;
	return m_pBinaryFile_Ex->Write(bytes);
}
