#ifndef _CORE_PATH_H_
#define _CORE_PATH_H_

#include "CsGlobal.h"

class CsString;

class CS_API CsPath
{
public:
	static cs_bool CreatePath(const CsString &, cs_int perms);
};

#endif // _CORE_PATH_H_