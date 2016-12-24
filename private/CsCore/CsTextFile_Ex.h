#ifndef _CORE_TEXT_DOCUMENT_EX_H_
#define _CORE_TEXT_DOCUMENT_EX_H_

#include "CsFile_Ex.h"

#define CS_CR    0x0d
#define CS_LF    0x0a
#define CS_CRLF  0x0d0a
#define CS_LFCR  0x0a0d

class CsTextFile_Ex 
	: public CsFile_Ex
{
public:
	CsTextFile_Ex(const CsString &sFileName);

	cs_byte Format() const;

	cs_bool GetChar(cs_uchar &);
	cs_bool PutChar(cs_uchar);

	cs_bool Read(cs_size_t size, CsString &);
	cs_bool ReadAll(CsString &);
	cs_bool Write(const CsString &);

protected:
	cs_cstring OpenMode() const;
};

#endif // _CORE_TEXT_DOCUMENT_EX_H_