#ifndef _CORE_PATH_H_
#define _CORE_PATH_H_

#include "gglobal.h"

class GString;

class GAPI GPath
{
public:
	static gbool CreatePath(const GString &, gint perms);
};

#endif // _CORE_PATH_H_