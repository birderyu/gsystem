#ifndef _CORE_SYNCHRONOUS_LOG_H_
#define _CORE_SYNCHRONOUS_LOG_H_

#include "gtype.h"
#include "gnocopyable.h"

namespace gsystem { // gsystem
namespace log { // gsystem.log

class GAPI GSynchronousLog
	: private GNocopyable
{
public:
	GSynchronousLog();
	~GSynchronousLog();

	gvoid Append(const GString &msg, gsize size);
	gvoid Flush();
};

} // namespace gsystem.log
} // namespace gsystem

#endif // _CORE_SYNCHRONOUS_LOG_H_
