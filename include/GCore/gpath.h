#ifndef _CORE_PATH_H_
#define _CORE_PATH_H_

#include "gglobal.h"

namespace gsystem { // gsystem

class GAPI GPath
{
public:
	static gbool CreatePath(const GString &, gint perms);
};

} // namespace gsystem

#endif // _CORE_PATH_H_