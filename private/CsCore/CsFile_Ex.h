#ifndef _CORE_FILE_PRIVATE_H_
#define _CORE_FILE_PRIVATE_H_

#include "CsFile.h"
#include "CsString.h"
#include <stdio.h>

class CsString;

class CsFile_Ex
{
public:
	CsFile_Ex(const CsString &sFileName);
	~CsFile_Ex();
	cs_bool Open(CsFile::CS_FILE_OPEN_MODE emOpenMode);
	cs_bool Close();
	cs_bool Read(cs_size_t len, CsBytes &tBytes);
	cs_bool ReadAll(CsBytes &tBytes);
	cs_bool Wirte(const CsBytes &tBytes);

protected:
	cs_bool CanRead(CsFile::CS_FILE_OPEN_MODE emOpenMode) const;
	cs_bool CanWrite(CsFile::CS_FILE_OPEN_MODE emOpenMode) const;
	FILE *m_pFileStream;
	CsString m_sFileName;
	CsFile::CS_FILE_OPEN_MODE m_emOpenMode;
};

#endif // _CORE_FILE_PRIVATE_H_