#ifndef _CORE_BINARY_DOCUMENT_EX_H_
#define _CORE_BINARY_DOCUMENT_EX_H_

#include "CsDocument_Ex.h"
#include "CsBytes.h"

class CsBinaryDocument_Ex
	: public CsDocument_Ex
{
public:
	CsBinaryDocument_Ex(const CsString &sFileName);
	virtual ~CsBinaryDocument_Ex();

	cs_void Flush();
	cs_void Abort();

	cs_bool Read(cs_size_t size, CsBytes &);
	cs_bool ReadAll(CsBytes &);
	cs_bool Wirte(const CsBytes &);

protected:
	cs_cstring OpenMode() const;

protected:
	CsBytes m_tBuffer; // »º³åÇø
};

#endif // _CORE_BINARY_DOCUMENT_EX_H_