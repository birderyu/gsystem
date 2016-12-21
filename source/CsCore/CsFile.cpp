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

cs_bool CsFile::Valid() const
{
	if (!m_pFileEx)
	{
		return false;
	}
	return m_pFileEx->Valid();
}
