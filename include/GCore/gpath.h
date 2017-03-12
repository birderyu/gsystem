#ifndef _CORE_PATH_H_
#define _CORE_PATH_H_

#include "gglobal.h"

namespace gnova { // gnova
	class GString;
} // namespace gnova

namespace gnova { // gnova

class GAPI GPath
{
public:
	static gbool CreatePath(const GString &, gint perms);
};

} // namespace gnova

#endif // _CORE_PATH_H_