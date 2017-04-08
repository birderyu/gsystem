#include "gbinfile.h"
#include "gbinfile_ex.h"

namespace gsystem { // gsystem

GBinFile::GBinFile(const GString &sFileName)
: GFile(new detail::GBinFile_Ex(sFileName))
{

}

GBinFile::GBinFile(detail::GBinFile_Ex *pBinaryFile_Ex)
: GFile(pBinaryFile_Ex)
{

}

gbool GBinFile::Read(gsize size, GBytes &bytes)
{
	if (!m_pFileEx)
	{
		return false;
	}
	detail::GBinFile_Ex *m_pBinaryFile_Ex = (detail::GBinFile_Ex*)m_pFileEx;
	return m_pBinaryFile_Ex->Read(size, bytes);
}

gbool GBinFile::ReadAll(GBytes &bytes)
{
	if (!m_pFileEx)
	{
		return false;
	}
	detail::GBinFile_Ex *m_pBinaryFile_Ex = (detail::GBinFile_Ex*)m_pFileEx;
	return m_pBinaryFile_Ex->ReadAll(bytes);
}

gbool GBinFile::Write(const GBytes &bytes)
{
	if (!m_pFileEx)
	{
		return false;
	}
	detail::GBinFile_Ex *m_pBinaryFile_Ex = (detail::GBinFile_Ex*)m_pFileEx;
	return m_pBinaryFile_Ex->Write(bytes);
}

} // namespace gsystem
