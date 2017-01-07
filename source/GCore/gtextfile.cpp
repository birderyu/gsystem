#include "gtextfile.h"
#include "gtextfile_ex.h"

GTextFile::GTextFile(const GString &sFileName)
: GFile(new GTextFile_Ex(sFileName))
{

}

GTextFile::GTextFile(GTextFile_Ex *pTextFile_Ex)
: GFile(pTextFile_Ex)
{

}

gbool GTextFile::Read(gsize size, GString &str)
{
	GASSERT(m_pFileEx);
	GTextFile_Ex *pTextFile_Ex = (GTextFile_Ex*)m_pFileEx;
	return pTextFile_Ex->Read(size, str);
}

gbool GTextFile::ReadAll(GString &str)
{
	GASSERT(m_pFileEx);
	GTextFile_Ex *pTextFile_Ex = (GTextFile_Ex*)m_pFileEx;
	return pTextFile_Ex->ReadAll(str);
}

gbool GTextFile::Write(const GString &str)
{
	GASSERT(m_pFileEx);
	GTextFile_Ex *pTextFile_Ex = (GTextFile_Ex*)m_pFileEx;
	return pTextFile_Ex->Write(str);
}
