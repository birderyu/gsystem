// 文本文件

#ifndef _CORE_TEXT_FILE_H_
#define _CORE_TEXT_FILE_H_

#include "CsFile.h"

class CS_API CsTextFile 
	: public CsFile
{
public:
	CsTextFile(const CsString &sFileName);
};

#endif // _CORE_TEXT_FILE_H_