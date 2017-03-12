#include "gbinaryfile.h"
#include "gbinaryfile_ex.h"

namespace gnova {

GBinaryFile::GBinaryFile(const GString &sFileName)
: GFile(new extra::GBinaryFile_Ex(sFileName))
{

}

GBinaryFile::GBinaryFile(extra::GBinaryFile_Ex *pBinaryFile_Ex)
: GFile(pBinaryFile_Ex)
{

}

gbool GBinaryFile::Read(gsize size, GBytes &bytes)
{
	if (!m_pFileEx)
	{
		return false;
	}
	extra::GBinaryFile_Ex *m_pBinaryFile_Ex = (extra::GBinaryFile_Ex*)m_pFileEx;
	return m_pBinaryFile_Ex->Read(size, bytes);
}

gbool GBinaryFile::ReadAll(GBytes &bytes)
{
	if (!m_pFileEx)
	{
		return false;
	}
	extra::GBinaryFile_Ex *m_pBinaryFile_Ex = (extra::GBinaryFile_Ex*)m_pFileEx;
	return m_pBinaryFile_Ex->ReadAll(bytes);
}

gbool GBinaryFile::Write(const GBytes &bytes)
{
	if (!m_pFileEx)
	{
		return false;
	}
	extra::GBinaryFile_Ex *m_pBinaryFile_Ex = (extra::GBinaryFile_Ex*)m_pFileEx;
	return m_pBinaryFile_Ex->Write(bytes);
}

}