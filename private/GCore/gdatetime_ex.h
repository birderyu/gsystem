#ifndef _CORE_DATETIME_PRIVATE_H
#define _CORE_DATETIME_PRIVATE_H

#include "gglobal_ex.h"

namespace gsystem { // gsystem
	class GDateTime;
	class GDate;
	class GTime;
} // namespace gsystem

namespace gsystem { // gsystem
namespace detail { // gsystem.detail

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

} // namespace gsystem.detail
} // namespace gsystem

#endif // _CORE_DATETIME_PRIVATE_H