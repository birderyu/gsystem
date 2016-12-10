#include "CsFile.h"
#include "CsFile_Ex.h"

CsFile::CsFile(const CsString &sFileName)
: m_pFile_Ex(new CsFile_Ex(sFileName))
{

}

CsFile::~CsFile()
{

}
