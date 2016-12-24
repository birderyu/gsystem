#ifndef _CORE_BINARY_FILE_EX_H_
#define _CORE_BINARY_FILE_EX_H_

#include "CsFile_Ex.h"

class CsBytes;

class CsBinaryFile_Ex
	: public CsFile_Ex
{
public:
	CsBinaryFile_Ex(const CsString &sFileName);
	virtual ~CsBinaryFile_Ex();

	cs_byte Format() const;

	cs_bool GetByte(cs_byte &);
	cs_bool PutByte(cs_byte);

	cs_bool Read(cs_size_t size, CsBytes &);
	cs_bool ReadAll(CsBytes &);
	cs_bool Write(const CsBytes &);

protected:
	cs_cstring OpenMode() const;
};

#endif // _CORE_BINARY_FILE_EX_H_