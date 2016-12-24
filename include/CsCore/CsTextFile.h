#ifndef _CORE_TEXT_FILE_H_
#define _CORE_TEXT_FILE_H_

#include "CsFile.h"

class CsTextFile_Ex;

class CS_API CsTextFile 
	: public CsFile
{
public:
	CsTextFile(const CsString &sFileName);

	cs_bool Read(cs_size_t size, CsString &);
	cs_bool ReadAll(CsString &);
	cs_bool Write(const CsString &);

protected:
	CsTextFile(CsTextFile_Ex *);
};

#endif // _CORE_TEXT_FILE_H_