#ifndef _CORE_DATETIME_PRIVATE_H
#define _CORE_DATETIME_PRIVATE_H

#include "gglobal_ex.h"

namespace gnova { // gnova
	class GDateTime;
	class GDate;
	class GTime;
} // namespace gnova

namespace gnova { // gnova
namespace detail { // gnova.detail

class GDateTime_Ex
{
public:
	static gbool GetNow(GDateTime &dt);
	static gbool GetNow(GDate &d);
	static gbool GetNow(GTime &t);

private:
	static gbool GetNow(guint &y, guint &m, guint &d, guint &dofw,
		guint &h, guint &mm, guint &s, guint &ms);
};

} // namespace gnova.detail
} // namespace gnova

#endif // _CORE_DATETIME_PRIVATE_H