// 二进制文档
#ifndef _CORE_BINARY_DOCUMENT_H_
#define _CORE_BINARY_DOCUMENT_H_

#include "CsDocument.h"

class CsBytes;
class CsBinaryDocument_Ex;

class CsBinaryDocument
	: public CsDocument
{
public:
	CsBinaryDocument(const CsString &sFileName);

	cs_bool Read(cs_size_t size, CsBytes &);
	cs_bool ReadAll(CsBytes &);
	cs_bool Wirte(const CsBytes &);

protected:
	CsBinaryDocument(CsBinaryDocument_Ex *);
};

#endif // _CORE_BINARY_DOCUMENT_H_