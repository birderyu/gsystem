#include "CsFile_Ex.h"
#include "CsBytes.h"

CsFile_Ex::CsFile_Ex(const CsString &sFileName)
: m_pFileStream(NULL)
, m_sFileName(sFileName)
, m_emOpenMode(CsFile::FILE_OPEN_MODE_NO_OPEN)
{

}

CsFile_Ex::~CsFile_Ex()
{
	if (m_pFileStream)
	{
		Close();
	}
}

cs_bool CsFile_Ex::Open(CsFile::CS_FILE_OPEN_MODE emOpenMode)
{
	m_emOpenMode = emOpenMode;
	return m_emOpenMode != CsFile::FILE_OPEN_MODE_NO_OPEN;
}

cs_bool CsFile_Ex::Close()
{
	if (NULL == m_pFileStream)
	{
		return false;
	}
	int ret = fclose(m_pFileStream);
	m_pFileStream = NULL;
	return ret == 0;
}

cs_bool CsFile_Ex::Read(cs_size_t len, CsBytes &tBytes)
{
	cs_byte bytes[1024];
	if (NULL == m_pFileStream || len == 0)
	{
		return false;
	}
	fread(bytes, sizeof(cs_byte), len, m_pFileStream);
	return tBytes.ReadFrom(bytes, len);
}

cs_bool CsFile_Ex::CanRead(CsFile::CS_FILE_OPEN_MODE emOpenMode) const
{
	return emOpenMode != CsFile::FILE_OPEN_MODE_NO_OPEN &&
		emOpenMode != CsFile::FILE_OPEN_MODE_ONLY_WIRTE;
}

cs_bool CsFile_Ex::CanWrite(CsFile::CS_FILE_OPEN_MODE emOpenMode) const
{
	return (emOpenMode | CsFile::FILE_OPEN_MODE_ONLY_WIRTE)
		== CsFile::FILE_OPEN_MODE_ONLY_WIRTE;
}
