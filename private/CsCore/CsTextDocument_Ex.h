#ifndef _CORE_TEXT_DOCUMENT_EX_H_
#define _CORE_TEXT_DOCUMENT_EX_H_

#include "CsDocument_Ex.h"
#include "CsStringBuffer.h"

#define CS_CR    0x0d
#define CS_LF    0x0a
#define CS_CRLF  0x0d0a
#define CS_LFCR  0x0a0d

class CsTextDocument_Ex 
	: public CsDocument_Ex
{
public:
	CsTextDocument_Ex(const CsString &sFileName);

	cs_void Flush();
	cs_void Abort();

	cs_bool ReadLine(CsString &);
	cs_bool WriteLine(const CsString &, cs_int format = CS_CRLF);

protected:
	cs_cstring OpenMode() const;

protected:
	CsStringBuffer m_tBuffer; // »º³åÇø
};

#endif // _CORE_TEXT_DOCUMENT_EX_H_