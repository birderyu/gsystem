#include "gtextfile.h"
#include "gtextfile_ex.h"

GTextFile::GTextFile(const GString &filename)
: GFile(new GTextFile_Ex(filename))
{

}

GTextFile::GTextFile(GTextFile_Ex *pTextFile_Ex)
: GFile(pTextFile_Ex)
{

}

gbool GTextFile::Read(gsize size, GString &content)
{
	GASSERT(m_pFileEx);
	GTextFile_Ex *pTextFile_Ex = (GTextFile_Ex*)m_pFileEx;
	return pTextFile_Ex->Read(size, content);
}

gbool GTextFile::ReadAll(GString &content)
{
	GASSERT(m_pFileEx);
	GTextFile_Ex *pTextFile_Ex = (GTextFile_Ex*)m_pFileEx;
	return pTextFile_Ex->ReadAll(content);
}

gbool GTextFile::Write(const GString &content)
{
	GASSERT(m_pFileEx);
	GTextFile_Ex *pTextFile_Ex = (GTextFile_Ex*)m_pFileEx;
	return pTextFile_Ex->Write(content);
}
