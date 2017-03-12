#ifndef _CORE_PATH_H_
#define _CORE_PATH_H_

#include "gglobal.h"

namespace gnova {
class GString;
}

namespace gnova {

class GAPI GPath
{
public:
	static gbool CreatePath(const GString &, gint perms);
};

}

#endif // _CORE_PATH_H_