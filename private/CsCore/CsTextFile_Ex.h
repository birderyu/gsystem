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
	CsTextFile_Ex(const GString &sFileName);

	gbyte Format() const;

	gbool GetChar(guchar &);
	gbool PutChar(guchar);

	gbool Read(gsize size, GString &);
	gbool ReadAll(GString &);
	gbool Write(const GString &);

protected:
	gcstring OpenMode() const;
};

#endif // _CORE_TEXT_DOCUMENT_EX_H_