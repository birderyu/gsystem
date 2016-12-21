// 文本文件
#ifndef _CORE_TEXT_DOCUMENT_H_
#define _CORE_TEXT_DOCUMENT_H_

#include "CsDocument.h"

class CsTextDocument_Ex;

class CS_API CsTextDocument 
	: public CsDocument
{
public:
	CsTextDocument(const CsString &sFileName);

	cs_bool Read(cs_size_t size, CsString &);
	cs_bool ReadAll(CsString &);
	cs_bool Write(const CsString &);

	cs_bool ReadLine(CsString &);
	cs_bool WriteLine(const CsString &);

protected:
	CsTextDocument(CsTextDocument_Ex *);
};

#endif // _CORE_TEXT_DOCUMENT_H_