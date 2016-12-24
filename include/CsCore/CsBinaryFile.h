#ifndef _CORE_BINARY_FILE_H_
#define _CORE_BINARY_FILE_H_

#include "CsFile.h"

class CsBytes;
class CsBinaryFile_Ex;

class CS_API CsBinaryFile
	: public CsFile
{
public:
	CsBinaryFile(const CsString &sFileName);

	cs_bool Read(cs_size_t size, CsBytes &);
	cs_bool ReadAll(CsBytes &);
	cs_bool Write(const CsBytes &);

protected:
	CsBinaryFile(CsBinaryFile_Ex *);
};

#endif // _CORE_BINARY_FILE_H_