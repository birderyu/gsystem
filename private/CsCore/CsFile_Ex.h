#ifndef _CORE_FILE_EX_H_
#define _CORE_FILE_EX_H_

#include "CsGlobal_Ex.h"

class CsFile_Ex
	: public CsNewT<CsFile_Ex>
{
public:
	virtual ~CsFile_Ex();
	virtual cs_bool Valid() const = 0;
};

#endif // _CORE_FILE_EX_H_